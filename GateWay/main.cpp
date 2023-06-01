#include <iostream>
#include <string>
#include "CommonUtility/Loger.h"
#include "ZmqMessager/DataSubscriber.h"
#include "ZmqMessager/DataPublisher.h"
#include "ZmqMessager/XProxy.h"

DEFINE_string(gateway_xsub_address, "tcp://127.0.0.1:6666", "xsub address");
DEFINE_string(gateway_xpub_address, "tcp://127.0.0.1:8888", "xpub address");
DEFINE_int32 (max_buff_size,102400,"Max Buffer Size for Message");

using namespace RS;

int main(int argc, char** argv)
{
    Loger::InitLog("GateWay");

    LOG_INFO<<"Gate Way Started...";

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    char* buff = (char*)malloc(FLAGS_max_buff_size);

    XProxy proxy(FLAGS_gateway_xpub_address, FLAGS_gateway_xsub_address);

    proxy.Create(NULL);

    free(buff);
	return 0;
}
