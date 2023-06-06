
#include <iostream>
#include <gflags/gflags.h>
#include "ClientConnection.h"
#include "Poco/NumberParser.h"

DEFINE_uint32(tcp_server_port, 2001, "TCP Server Port");

using Poco::UInt16;
using Poco::NumberParser;

#if defined(POCO_OS_FAMILY_WINDOWS)
	NamedEvent terminator(ProcessImpl::terminationEventName(Process::id()));
#else
	Event terminator;
#endif
typedef TCPServerConnectionFactoryImpl<ClientConnection> TCPFactory;

int main(int argc, char** argv)
{
	try
	{
        gflags::ParseCommandLineFlags(&argc, &argv, true);

		Poco::UInt16 port = FLAGS_tcp_server_port;

		TCPServer srv(new TCPFactory(), port);
		srv.start();

		std::cout << "TCP server listening on port " << port << '.'
			 << std::endl << "Press Ctrl-C to quit." << std::endl;

		terminator.wait();
	}
	catch (Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}

	return 0;
}