#include "DataSubscriber.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <zmq.h>
#include <vector>
using namespace std;
using namespace RS;

DataSubscriber::DataSubscriber(string address) {
	ctx = zmq_ctx_new();
	subscriber = zmq_socket(ctx, ZMQ_SUB);

	//set hight water mark unlimited
	int highwatermark = 0;
	zmq_setsockopt(subscriber, ZMQ_RCVHWM, &highwatermark, sizeof(highwatermark));
	int timeout = 1000;
	zmq_setsockopt(subscriber, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
	int rc = zmq_connect(subscriber, address.c_str());
	if (rc != 0)
	{
		//LOG_ERROR<<"!!!Subscriber can not connect to Publisher";
	}
}

void DataSubscriber::SetNoTopicFilter() {
	zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
}

void DataSubscriber::SetTopicFilter(vector<string> topics) {
	for (auto topic : topics)
	{
		zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
		// Loger::Trace("Subscirber will receive "+topic+" message");
	}
}

DataSubscriber::~DataSubscriber() {
	zmq_close(subscriber);
	zmq_ctx_destroy(ctx);
}



int DataSubscriber::GetMsg(char* bufData, int bufLen) {

	int more;
	size_t more_size = sizeof(more);
	int rslen = 0;
	do {
		memset(bufData,'\0', bufLen);
		int msg_size=zmq_recv(subscriber, bufData, bufLen, 0);
		int rc = zmq_getsockopt(subscriber, ZMQ_RCVMORE, &more, &more_size);
		if (msg_size < 0)
		{
			int error_code = zmq_errno();
			//LOG_ERROR<<"Subscirber Get Msg Error";
		}
		rslen = msg_size;

	} while (more);
	return rslen;

}

