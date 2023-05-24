#include <iostream>
#include <string>
#include "CommonUtility/Loger.h"
#include "ZmqMessager/DataSubscriber.h"
#include "ZmqMessager/DataPublisher.h"
#include "ZmqMessager/XProxy.h"

DEFINE_bool(log_debug, true, "log debug");

DEFINE_string(xsub_address, "tcp://127.0.0.1:6666", "xsub address");
DEFINE_string(xpub_address, "tcp://127.0.0.1:8888", "xpub address");


#define MaxBuffSize 102400

using namespace RS;

void GateWay()
{
    Loger::Trace("MSG");
}

int main(int argc, char** argv)
{
    google::ParseCommandLineFlags(&argc, &argv, true);

    Loger::Init("datagateway.log");
    Loger::Trace("Data GateWay Start...");

    char* buff = (char*)malloc(MaxBuffSize);

    XProxy proxy(FLAGS_xpub_address, FLAGS_xsub_address);

    proxy.Create(NULL);

   
    free(buff);
	return 0;
}
