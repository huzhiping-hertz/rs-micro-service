
#include <iostream>
#include "gflags/gflags.h"
#include "CommonUtility/Loger.h"
#include <drogon/WebSocketClient.h>
#include <drogon/HttpAppFramework.h>

DEFINE_string(websocket_client_ip, "127.0.0.1", "web socket ip");
DEFINE_int32(websocket_client_port, 9980, "web socket port");

using namespace drogon;
using namespace std;


int main(int argc, char* argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    string path="/ws";
    string serverString = "ws://"+FLAGS_websocket_client_ip+":"+to_string(FLAGS_websocket_client_port);

    auto wsPtr = WebSocketClient::newWebSocketClient(serverString);
    auto req = HttpRequest::newHttpRequest();
    req->setPath(path);

    wsPtr->setMessageHandler([](const std::string& message,
        const WebSocketClientPtr&,
        const WebSocketMessageType& type) {
            std::string messageType = "Unknown";
            if (type == WebSocketMessageType::Text)
                messageType = "text";
            else if (type == WebSocketMessageType::Pong)
                messageType = "pong";
            else if (type == WebSocketMessageType::Ping)
                messageType = "ping";
            else if (type == WebSocketMessageType::Binary)
                messageType = "binary";
            else if (type == WebSocketMessageType::Close)
                messageType = "Close";

            LOG_INFO << "new message (" << messageType << "): " << message;
        });

    wsPtr->setConnectionClosedHandler([](const WebSocketClientPtr&) {
       LOG_TRACE<<"WebSocket connection closed!";
        });


    wsPtr->connectToServer(
        req,
        [](ReqResult r,
            const HttpResponsePtr&,
            const WebSocketClientPtr& wsPtr) {
                if (r != ReqResult::Ok)
                {
                    LOG_ERROR<<"Failed to establish WebSocket connection!";
                    wsPtr->stop();
                    return;
                }
                LOG_TRACE<<"WebSocket connected!";
                //wsPtr->getConnection()->setPingMessage("", 2s);
                //wsPtr->getConnection()->send("hello!");
        });

    // Quit the application after 15 seconds
    app().getLoop()->runAfter(30, []() { app().quit(); });

   // app().setLogLevel(trantor::Logger::kDebug);
    app().run();
    return 0;
}