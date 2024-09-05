#include "INotificationRepository.h"
#include "Note.h"
#include "NotificationRepository.h"
#include "MessageReceiver.h"
#include "INotifier.h"
#include "TimerService.h"
#include "GNotifier.h"

#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <memory>

int main(int argc, const char *argv[])
{
    // Менеджер уведомлений
    std::unique_ptr<notifications::INotifier> notifier = std::make_unique<notifications::GNotifier>();

    // Подключение к БД
    std::unique_ptr<notifications::INotificationRepository> repository = 
        std::make_unique<notifications::NotificationRepository>("db.sqlite3");

    // Таймер отслеживания событий
    notifications::time::TimerService timer(1000, 
        [](notifications::INotificationRepository *repo, notifications::INotifier *no) { 
            notifications::Notification notif("Тестовое напоминание", 
                boost::posix_time::from_iso_string("20020120T235959"));
            no->notify(notif);
        }, std::make_tuple(repository.get(), notifier.get()));

    // Сервис взаимодействия с внешней управляющей программой
    boost::interprocess::message_queue::remove("message_queue");
    notifications::communication::MessageReceiver receiver([](notifications::INotificationRepository *r){ r->reloadRepository(); },
            repository.get(), nullptr);

    timer.start();
    while(true) {}

    return 0;
}
