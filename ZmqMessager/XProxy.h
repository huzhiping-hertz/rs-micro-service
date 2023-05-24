#ifndef XPROXY_H
#define XPROXY_H

#include <string>

namespace RS {

	using namespace std;

	class XProxy {

	private:
		void* ctx;
		void* frontend;
		void* backend;
	public:
		XProxy(string xpub, string xsub);
		void Create(void* captrue);
		~XProxy();
	};
} // namespace ZmqMessager

#endif
