#include <boost/interprocess/ipc/message_queue.hpp>

using namespace boost::interprocess;

int main ()
{
    char data[100] = "Db has been updated";
    message_queue mq
        (open_or_create
        ,"message_queue"
        ,100
        ,sizeof(char) * 100
        );


    for(int i = 0; i < 10; ++i)
        mq.send(data, sizeof(char) * 100, 0);
    return 0;
}
