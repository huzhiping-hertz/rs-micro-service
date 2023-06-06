#include "ClientConnection.h"
#include "CommonUtility/Loger.h"
#include <string>

ClientConnection::ClientConnection(const StreamSocket &s) : TCPServerConnection(s)
{
}

void ClientConnection::run()
{
    StreamSocket &ss = socket();
    try
    {
        char buffer[256]={0};
        int n = ss.receiveBytes(buffer, sizeof(buffer));
        while (n > 0)
        {
            LOG_INFO<< "Received " << n << " bytes:" << std::string(buffer);
            memset(buffer,'\0',256);
            n = ss.receiveBytes(buffer, sizeof(buffer));
        }
    }
    catch (Exception &exc)
    {
        LOG_ERROR << "ClientConnection: " << exc.displayText();
    }
}
