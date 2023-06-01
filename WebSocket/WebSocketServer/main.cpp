#include "WebSocketServer.h"
#include "gflags/gflags.h"
#include "CommonUtility/Loger.h"

DEFINE_string(websocket_server_sub_address, "tcp://127.0.0.1:8888", "zmq address");
DEFINE_string(websocket_server_pub_address, "tcp://127.0.0.1:6666", "zmq address");

DEFINE_string(websocket_server_ip, "127.0.0.1", "web socket ip");
DEFINE_int32(websocket_server_port,9980, "web socket port");

using namespace RS;

int main(int argc, char** argv)
{
	gflags::ParseCommandLineFlags(&argc, &argv, true);

	WebSocketServer server;
	server.run(argc,argv);
}