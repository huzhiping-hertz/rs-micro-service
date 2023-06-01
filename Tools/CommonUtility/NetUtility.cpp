#include "NetUtility.h"
#include <Poco/Net/ICMPClient.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <map>
#include <sstream>

using namespace RM;
using namespace Poco::Net;
using namespace Poco;

bool NetUtility::Ping(string ipAddress)
{
    try {
        ICMPClient icmp(IPAddress::IPv4);
        int rs = icmp.ping(ipAddress);
        return rs > 0;
    }
    catch (Exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return false;
    }
}


string NetUtility::PostRequest(string url, string body, map<string, string> headers) {
    try
    {
        URI uri(url);
        HTTPClientSession session(uri.getHost(), uri.getPort());
        string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
        req.setContentType("application/json");

        for (map<string, string>::iterator it = headers.begin();
           it != headers.end(); it++) {
           req.set(it->first, it->second);
        }

        req.setContentLength(body.length());

        std::ostream& os = session.sendRequest(req);
        os << body;  // sends the body

        HTTPResponse res;
        cout << res.getStatus() << " " << res.getReason() << endl;

        istream& is = session.receiveResponse(res);
        stringstream ss;
        StreamCopier::copyStream(is, ss);

        return ss.str();

    }
    catch (Exception& ex)
    {
        cerr << ex.displayText() << endl;
        return "";
    }
}
