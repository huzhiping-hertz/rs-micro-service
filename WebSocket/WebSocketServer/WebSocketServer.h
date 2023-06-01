#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include <iostream>

#include "RequestHandlerFactory.h"
#include "CommonUtility/Loger.h"

using namespace RS;

using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;

DECLARE_int32(websocket_server_port);
DECLARE_string(websocket_server_ip);

class WebSocketServer : public Poco::Util::ServerApplication
{
public:
	WebSocketServer() : _helpRequested(false)
	{
		
	}

	~WebSocketServer()
	{
	}

protected:
	void initialize(Application& self)
	{
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "display help information on command line arguments")
			.required(false)
			.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A WebSocket Server For TSME6.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args)
	{
		LOG_TRACE<<"websocket server started.";

		if (_helpRequested)
		{
			displayHelp();
		}
		else
		{
			unsigned short port = (unsigned short)FLAGS_websocket_server_port;
			//ServerSocket svs(port);
			Poco::Net::SocketAddress sa(FLAGS_websocket_server_ip,to_string(FLAGS_websocket_server_port));
			ServerSocket svs(sa);
			HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);
			srv.start();
			// wait for CTRL-C or kill
			waitForTerminationRequest();
			srv.stop();
		}
		return Application::EXIT_OK;
	}

private:
	bool _helpRequested;
};