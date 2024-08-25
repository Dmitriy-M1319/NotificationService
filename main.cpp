#include "INotificationRepository.h"
#include "MessageReceiver.h"
#include "INotifier.h"
#include "TimerService.h"
#include "GNotifier.h"

#include <iostream>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <thread>
#include <memory>

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

void test_receiver()
{
    boost::interprocess::message_queue::remove("message_queue");
    notifications::communication::MessageReceiver receiver([](notifications::INotificationRepository *r){},
            nullptr);
    int a;
    std::cin >> a;
    receiver.stopReceiving();
}

int main(int argc, const char *argv[])
{
    //test_timer();
    test_receiver();
    return 0;
}
