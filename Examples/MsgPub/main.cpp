#include "ZmqMessager/DataPublisher.h"
#include "CommonUtility/Loger.h"

DEFINE_string(zmq_address, "tcp://127.0.0.1:6666", "zmq address");
DEFINE_bool(log_debug, true, "log debug");
using namespace std;
using namespace RS;

int main(int argc, char** argv)
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    //Loger::Init("pub.log");
    //Loger::Trace("Publisher address "+FLAGS_zmq_address);

    DataPublisher* ptrPublisher = DataPublisher::GetInstance(FLAGS_zmq_address,true);

    string msg_topic = "tsme6";

    for (int i = 0; i < 1000; i++)
    {
        zmq_sleep(1);
        string msg_data = "ZMQ Num "+to_string(i);
        ptrPublisher->SendMsg((char*)msg_data.c_str(), msg_data.length(), msg_topic);
        //Loger::Trace("Send Topic Msg:" + msg_data);
        std::cout << msg_data << endl;
        ptrPublisher->SendMsg((char*)msg_data.c_str(), msg_data.length(), "ACD");
        //Loger::Trace("Send No Topic Msg:" + msg_data);
        
    }


    return 0;
}