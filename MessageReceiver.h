#pragma once

#include "INotificationRepository.h"
#include "ISerializer.h"

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
    const std::size_t messageLength = 400;
    MessageReceiver(DbReloadCallback callback, INotificationRepository *repo, ISerializer *serializer);
    ~MessageReceiver();
    void stopReceiving();
private:
    boost::interprocess::message_queue m_queue;
    std::atomic<bool> m_stop = false;
    INotificationRepository *m_repo;
    ISerializer *m_serializer;
    std::thread m_ReceiverThread;
    DbReloadCallback m_callback;
};

}
}
