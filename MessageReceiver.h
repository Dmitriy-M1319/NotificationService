#pragma once

#include "INotificationRepository.h"

#include <boost/interprocess/ipc/message_queue.hpp>
#include <atomic>
#include <thread>
#include <functional>


namespace notifications
{

using DbReloadCallback = std::function<void(INotificationRepository *)>;
namespace communication
{

class MessageReceiver
{
public:
    MessageReceiver(DbReloadCallback callback, INotificationRepository *repo);
    void startReceiving();
    void stopReceiving();
private:
    std::atomic<bool> m_stop = false;
    INotificationRepository *m_repo;
    std::thread m_ReceiverThread;
    DbReloadCallback m_callback;
    boost::interprocess::message_queue m_queue;
};

}
}
