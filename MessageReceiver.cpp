#include "MessageReceiver.h"

#include <iostream>
#include <cstring>

using namespace notifications::communication;
using namespace boost::interprocess;


MessageReceiver::MessageReceiver(DbReloadCallback callback, INotificationRepository *repo):
    m_repo(repo), m_callback(callback),
    m_ReceiverThread([&](){
        char msg[messageLength];
        unsigned int priority;
        message_queue::size_type recvd_size;
        while(true && !m_stop) {
            m_queue.receive(msg, messageLength, recvd_size, priority);
            if(!std::strcmp(msg, "Db has been updated")) {
                // пока просто делаем печать в терминал
                std::cout << "good" << std::endl;
            }
        }
    }),
    m_queue(open_or_create, "message_queue", 100, 100 * sizeof(char))  {}


void MessageReceiver::stopReceiving() {
    m_stop = true;
    m_ReceiverThread.join();
}
