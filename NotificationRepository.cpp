#include "NotificationRepository.h"

#include <algorithm>
#include <filesystem>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <sqlite/query.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/result.hpp>
#include <stdexcept>
#include <string>
#include <format>

using namespace notifications;

NotificationRepository::NotificationRepository(const std::string& connString) 
{
    if(!std::filesystem::exists(connString)) {
        std::filesystem::path p(connString);
        std::ofstream ofs(p);
        ofs.close();

        m_connection = std::make_unique<sqlite::connection>(connString);
        auto createQuery = "CREATE TABLE notifications(id INTEGER PRIMARY KEY, text TEXT, date TEXT);";
        sqlite::execute(*m_connection, createQuery, true);
    }
    else {
        m_connection = std::make_unique<sqlite::connection>(connString);
    }
}

NotificationRepository::~NotificationRepository()
{
    // Сохраняем все при отключении компьютера или выхода из сеанса ОС
    constexpr auto updateQueryTemplate = "UPDATE notifications SET text=\'{}\', not_date=\'{}\' WHERE id={};";
    constexpr auto insertQueryTemplate = "INSERT INTO notifications VALUES(\'{}\'. \'{}\');";

    try {
        for(const Notification& note: m_notifications) {
            if(note.id()) {
                sqlite::execute(*m_connection, 
                    std::format(updateQueryTemplate, note.text(), boost::posix_time::to_simple_string(note.notificationDate()), note.id()));
            } else {
                sqlite::execute(*m_connection, 
                    std::format(insertQueryTemplate, note.text(), boost::posix_time::to_simple_string(note.notificationDate())));
            }
        }
    } catch (...) {
        // добавить логгирование в Google Log
        std::cerr << "Failed to sync data with database" << std::endl;
    }
    m_notifications.clear();
}


const std::vector<Notification>& NotificationRepository::activeNotifications()
{
    if(!m_notifications.empty())
        return m_notifications;

    const char *query = "SELECT text, not_date FROM notifications WHERE datetime(not_date) > datetime('now');";
    sqlite::query q(*m_connection, query);
    boost::shared_ptr<sqlite::result> cursor = q.get_result(); 
    while(cursor->next_row()) {
        m_notifications.emplace_back(cursor->get_string(1), time_from_string(cursor->get_string(2)));
    }

    return m_notifications;
}

Notification& NotificationRepository::getNotificationById(unsigned int id)
{
    sqlite::query q(*m_connection, std::format("SELECT text, not_date FROM notifications WHERE id={};", id));
    boost::shared_ptr<sqlite::result> cursor = q.get_result(); 
    if(cursor->next_row())
        m_currNotification = Notification(cursor->get_string(1), time_from_string(cursor->get_string(2)));
    return m_currNotification;
}

void NotificationRepository::saveNotification(const Notification &note)
{
   m_notifications.push_back(note); 
}


void NotificationRepository::updateNotification(unsigned int id, const Notification &note)
{
   auto updated = std::find_if(m_notifications.begin(), m_notifications.end(), 
           [&](const Notification& n) { return n.id() == id;});
   if(updated == m_notifications.end())
       throw std::range_error{"Notification with this id not found"};

   updated->setText(note.text());
   updated->setNotificationDate(note.notificationDate());
}

void NotificationRepository::deleteNotification(unsigned int id)
{
    auto updated = std::find_if(m_notifications.begin(), m_notifications.end(), 
           [&](const Notification& n) { return n.id() == id;});
   if(updated == m_notifications.end())
       throw std::range_error{"Notification with this id not found"};

    m_notifications.erase(updated);
}
