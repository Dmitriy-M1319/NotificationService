#include "MessageReceiver.h"


#include <cstring>

using namespace notifications::communication;
using namespace boost::interprocess;


MessageReceiver::MessageReceiver(DbReloadCallback callback, INotificationRepository *repo, ISerializer *serializer):
    m_repo(repo), m_callback(callback), m_serializer(serializer),
    m_ReceiverThread([&](){
        char msg[messageLength];
        unsigned int priority;
        message_queue::size_type recvd_size;
        while(true && !m_stop) {
            m_queue.receive(msg, messageLength, recvd_size, priority);
            std::string data(msg); 
            auto simpleNote = m_serializer->deserialize(data);
            auto notif = simpleNote.toNote();

            std::string answer = "OK";
            switch (simpleNote.operation) {
                case notifications::NoteSerialization::OperationType::INSERT:
                    repo->saveNotification(notif);
                    break;
                case notifications::NoteSerialization::OperationType::UPDATE:
                    repo->updateNotification(simpleNote.id, notif);
                    break;
                case notifications::NoteSerialization::OperationType::DELETE:
                    repo->deleteNotification(simpleNote.id);
                    break;
                default:
                    // лог о неуспешной операции
                    answer = "Error";
            };
            
            m_queue.send(answer.c_str(), answer.size(), priority);
        }
    }),
    m_queue(open_or_create, "message_queue", 100, 100 * sizeof(char))  {}

MessageReceiver::~MessageReceiver() {
    if(!m_stop)
        stopReceiving();
}


void MessageReceiver::stopReceiving() {
    m_stop = true;
    m_ReceiverThread.join();
}
