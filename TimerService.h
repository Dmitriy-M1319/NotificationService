#pragma once

#include "INotificationRepository.h"
#include "INotifier.h"

#include <string>
#include <atomic>
#include <mutex>
#include <chrono>
#include <thread>
#include <tuple>
#include <functional>

using namespace std::chrono;


namespace notifications
{

//using NotificateCallback = std::function<void(INotificationRepository *, INotifier *)>;
using NotificateCallback = std::function<void(const std::string&, int)>;

//using NotificateArgs = std::tuple<INotificationRepository *, INotifier *>;
using NotificateArgs = std::tuple<std::string, int>;

namespace time 
{

class TimerService
{
public:
    TimerService(std::size_t time,  NotificateCallback func, NotificateArgs args);
    void start();
    void stop();
private:
    milliseconds m_time;
    std::mutex m_mtx;
    std::thread m_timerThread;
    std::atomic<bool> m_timerRunCondition = true;
    time_point<system_clock> m_start;
    NotificateCallback m_callback;
    NotificateArgs m_args;
};

}
}
