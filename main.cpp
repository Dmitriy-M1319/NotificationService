#include "INotificationRepository.h"
#include "Note.h"
#include "NotificationRepository.h"
#include "MessageReceiver.h"
#include "INotifier.h"
#include "TimerService.h"
#include "GNotifier.h"

#include <iostream>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <thread>
#include <memory>
#include <ctime>

#if 0
void test_timer()
{
    std::unique_ptr<notifications::INotifier> n = std::make_unique<notifications::GNotifier>();

    notifications::time::TimerService timer(1000, 
            [](int val, notifications::INotifier *no) { 
                notifications::Notification notif("Тестовое напоминание", 
                    boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
                no->notify(notif);
            }, 
            std::make_tuple(5, n.get()));

    timer.start();
    std::this_thread::sleep_for(5000ms);
    timer.stop();
}
#endif

void test_receiver()
{
    notifications::communication::MessageReceiver receiver([](notifications::INotificationRepository *r){},
            nullptr);
    int a;
    std::cin >> a;
    receiver.stopReceiving();
}

void test_database() 
{
    std::unique_ptr<notifications::INotificationRepository> repository = 
        std::make_unique<notifications::NotificationRepository>("db.sqlite3");
    
    /*for(int i = 1; i < 10; ++i) {
        notifications::Notification note(std::format("note {}", i), boost::posix_time::from_time_t(time(nullptr)));
        repository->saveNotification(note);
    }*/
    

    for(auto& val: repository->activeNotifications()) {
        std::cout << val.id() << " " << val.text() << " " << val.notificationDate() << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    test_database();
    /*
    // Менеджер уведомлений
    std::unique_ptr<notifications::INotifier> notifier = std::make_unique<notifications::GNotifier>();

    // Подключение к БД
    std::unique_ptr<notifications::INotificationRepository> repository = 
        std::make_unique<notifications::NotificationRepository>("db.sqlite3");

    // Таймер отслеживания событий
    notifications::time::TimerService timer(1000, 
        [](notifications::INotificationRepository *repo, notifications::INotifier *no) { 
            notifications::Notification notif("Тестовое напоминание", 
                boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
            no->notify(notif);
        }, std::make_tuple(repository.get(), notifier.get()));

    // Сервис взаимодействия с внешней управляющей программой
    boost::interprocess::message_queue::remove("message_queue");
    notifications::communication::MessageReceiver receiver([](notifications::INotificationRepository *r){ r->reloadRepository(); },
            repository.get());
    */

    return 0;
}
