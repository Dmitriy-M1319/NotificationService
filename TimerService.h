#pragma once

#include "INotificationRepository.h"
#include "INotifier.h"

#include <chrono>
#include <thread>
#include <mutex>
#include <functional>


namespace notifications
{
namespace time 
{

class TimerService
{
public:
    TimerService(std::size_t time, std::function<void(INotificationRepository *, INotifier *)> func);
private:
    std::chrono::milliseconds m_time;
    std::thread m_timerThread;
    std::mutex m_mtx;
};

}
}
