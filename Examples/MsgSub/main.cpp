#include "ZmqMessager/DataSubscriber.h"
#include "CommonUtility/Loger.h"
#include <vector>

DEFINE_string(zmq_address, "tcp://127.0.0.1:8888", "zmq address");
using namespace RS;
using namespace std;

int main(int argc, char** argv)
{
    Loger::InitLog("sub");

    gflags::ParseCommandLineFlags(&argc, &argv, true);
    
    char msg[1000] = { '\0' };
    char nomsg[1000] = { '\0' };
    DataSubscriber subscriber = DataSubscriber(FLAGS_zmq_address);
    vector<string> topics;
    topics.push_back("ACD");
    topics.push_back("POW");
    subscriber.SetTopicFilter(topics);
    while (true)
    {
        int len = subscriber.GetMsg(msg, 1000);
        LOG_INFO<<"Receive Topic Msg:" + string(msg);
       // noTopicSub.GetMsg(nomsg, 1000);
       // Loger::Trace("Receive No Topic Msg:" + string(nomsg));
    }

    return 0;
}