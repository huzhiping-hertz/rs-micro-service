#ifndef NETUtility_H
#define NETUtility_H

#include <iostream>
#include <string>
#include <map>

namespace RM
{
	using namespace std;

	class NetUtility
	{
	private:
		NetUtility() {}

	public:
		static bool Ping(string ipAddress);
		static string PostRequest(string url, string body, map<string, string> headers);
	};
}
#endif