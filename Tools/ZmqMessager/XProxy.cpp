#include "XProxy.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <zmq.h>
using namespace std;
using namespace RS;

XProxy::XProxy(string xpub,string xsub) {
	ctx = zmq_ctx_new();

	frontend = zmq_socket(ctx, ZMQ_XPUB);
	backend = zmq_socket(ctx, ZMQ_XSUB);
	int pub_rs=zmq_bind(frontend, xpub.c_str());
	int sub_rs=zmq_bind(backend, xsub.c_str());

	// Loger::Trace("XPub address:" + xpub);
	// Loger::Trace("XSub address:" + xsub);

	if (pub_rs != 0 || sub_rs!=0)
	{
		//LOG_ERROR<<"!!!XPub or XSub can not be established";
	}
}

void XProxy::Create(void* captrue)
{
	zmq_proxy(frontend, backend, captrue);
	//zmq_proxy_steerable(frontend, backend, nullptr, nullptr);
}

XProxy::~XProxy() {
	zmq_close(frontend);
	zmq_close(backend);
	zmq_ctx_destroy(ctx);
}

