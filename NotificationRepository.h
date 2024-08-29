#pragma once

#include "INotificationRepository.h"
#include <sqlite/connection.hpp>
#include <memory>

namespace notifications
{

class NotificationRepository: public INotificationRepository
{
public:
    NotificationRepository(const std::string& connString);
    ~NotificationRepository();
    const std::vector<Notification>& activeNotifications() override;
    Notification& getNotificationById(unsigned int id) override;
    void reloadRepository() override;
    void saveNotification(const Notification &note) override;
    void saveNotificationAsync(const Notification &note) ;
    void updateNotification(unsigned int id, const Notification &note) override;
    void updateNotificationAsync(unsigned int id, const Notification &note);

    void deleteNotification(unsigned int id) override;
    
private:
    std::unique_ptr<sqlite::connection> m_connection;
};

}; // notifications
