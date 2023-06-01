#include "ZmqMessager/DataPublisher.h"
#include "CommonUtility/Loger.h"
#include <thread>

DEFINE_string(zmq_address, "tcp://127.0.0.1:6666", "zmq address");

using namespace std;
using namespace RS;

int main(int argc, char** argv)
{
    Loger::InitLog("pub");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    
    LOG_INFO<<"Publisher address "+FLAGS_zmq_address;

    DataPublisher* ptrPublisher = DataPublisher::GetInstance(FLAGS_zmq_address,true);

    string msg_topic = "POW";

    for (int i = 0; i < 1000; i++)
    {
        
        string msg_data = "ZMQ Num "+to_string(i);
        ptrPublisher->SendMsg((char*)msg_data.c_str(), msg_data.length(), msg_topic);
        LOG_INFO<<"Send Topic Msg:" + msg_data;
        ptrPublisher->SendMsg((char*)msg_data.c_str(), msg_data.length(), "ACD");
        LOG_INFO<<"Send No Topic Msg:" + msg_data;
        std::this_thread::sleep_for(1000ms);
        
    }


    return 0;
}