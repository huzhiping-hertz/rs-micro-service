#include "ZmqMessager/DataSubscriber.h"
#include "CommonUtility/Loger.h"
#include <vector>

DEFINE_string(zmq_address, "tcp://127.0.0.1:8888", "zmq address");
//DEFINE_string(zmq_address, "ipc://rspipeline", "zmq address");
DEFINE_bool(log_debug, true, "log debug");
using namespace RS;
using namespace std;

int main(int argc, char** argv)
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    //Loger::Init("sub.log");
    char msg[1000] = { '\0' };
    char nomsg[1000] = { '\0' };
    DataSubscriber subscriber = DataSubscriber(FLAGS_zmq_address);
    vector<string> topics;
    topics.push_back("ACD");
    subscriber.SetTopicFilter(topics);
    //DataSubscriber noTopicSub = DataSubscriber("Test2");
    while (true)
    {
        int len = subscriber.GetMsg(msg, 1000);
        //Loger::Trace("Receive Topic Msg:" + string(msg));
        std::cout << string(msg) << endl;
       // noTopicSub.GetMsg(nomsg, 1000);
       // Loger::Trace("Receive No Topic Msg:" + string(nomsg));
    }

    return 0;
}