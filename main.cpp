#include "INotificationRepository.h"
#include "INotifier.h"
#include "TimerService.h"
#include "GNotifier.h"

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

int main(int argc, const char *argv[])
{
    test_timer();
    return 0;
}
