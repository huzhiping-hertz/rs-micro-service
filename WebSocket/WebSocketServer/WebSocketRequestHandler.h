#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include <iostream>

#include "ZmqMessager/DataSubscriber.h"
#include "CommonUtility/Loger.h"

using namespace RS;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;

DECLARE_string(websocket_server_sub_address);

const int max_length = 1024000;
class WebSocketRequestHandler : public HTTPRequestHandler
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		DataSubscriber subscriber = DataSubscriber(FLAGS_websocket_server_sub_address);
		subscriber.SetNoTopicFilter();

		char* data=(char*)malloc(max_length);
		try
		{
			WebSocket ws(request, response);
			LOG_TRACE<<"websocket connection established.";
			LOG_TRACE<<"Wait message from pipeline.";
			int len;
			int rs=0;
			do
			{
				memset(data, '\0', max_length);
				len = subscriber.GetMsg(data, max_length);
				if (len > 0)
				{
					rs = ws.sendFrame(data, len);
				}
			} while ( WebSocket::FRAME_OP_BITMASK != WebSocket::FRAME_OP_CLOSE);
			//} while (rs > 0);
			LOG_TRACE<<"websocket connection closed.";
            delete data;
		}
		catch (WebSocketException& exc)
		{
			switch (exc.code())
			{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
			LOG_ERROR<<"exception websocket connection closed."+exc.displayText();
            delete data;
		}
	}
};

