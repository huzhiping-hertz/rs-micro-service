#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/StreamSocket.h"

#include "Poco/Logger.h"
#include "Poco/Process.h"
#include "Poco/NamedEvent.h"
#include <iostream>

using Poco::Net::StreamSocket;
using Poco::Net::TCPServer;
using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnectionFactoryImpl;

using Poco::Event;
using Poco::Exception;
using Poco::NamedEvent;
using Poco::Process;
using Poco::ProcessImpl;

class ClientConnection : public TCPServerConnection
{
public:
    ClientConnection(const StreamSocket &s);

    void run();
};

#endif