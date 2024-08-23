#include "TimerService.h"
#include "GNotifier.h"

#include <boost/date_time/posix_time/time_parsers.hpp>
#include <iostream>
#include <thread>
#include <memory>

void test_timer()
{
    notifications::time::TimerService timer(1000, 
            [](const std::string text, int val) { std::cout << "Text: " << text << ", val: " << val << std::endl; },
            std::make_tuple("Some text", 5));

    timer.start();
    std::this_thread::sleep_for(5000ms);
    timer.stop();
}

void test_notify()
{
    std::unique_ptr<notifications::INotifier> n = std::make_unique<notifications::GNotifier>();
    notifications::Notification notif("Тестовое напоминание", 
            boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
    n->notify(notif);
}

int main(int argc, const char *argv[])
{
    test_notify(); 
    return 0;
}
