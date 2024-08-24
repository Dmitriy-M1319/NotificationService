#include "TimerService.h"

using namespace notifications::time;

TimerService::TimerService(std::size_t time,  NotificateCallback func, NotificateArgs args):
    m_time(time), m_callback(func), m_args(args) ,
    m_timerThread([&]() {
            m_mtx.lock();
            m_start = system_clock::now(); 
            while(true && m_timerRunCondition) {
                auto currentTime = std::chrono::system_clock::now();
                if(duration_cast<milliseconds>(currentTime - m_start) == m_time) {
                    // TODO: подумать над асинхронным запуском колбека, чтобы не стопить таймер через мьютекс
                    m_callback(std::get<0>(m_args), std::get<1>(m_args));
                    m_start = currentTime;
                }
            }
            m_mtx.unlock();
        }) { m_mtx.lock(); }

void TimerService::start() {
    m_mtx.unlock();
}

void TimerService::stop() {
    m_timerRunCondition = false;
    m_timerThread.join();
}
