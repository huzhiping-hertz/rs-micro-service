#include "DataPublisher.h"
#include <iostream>
#include <iomanip>
#include "zmq.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <ctime> 
#include <time.h>
#include "trantor/utils/Logger.h"
#include "trantor/utils/AsyncFileLogger.h"

using namespace RS;
using json = nlohmann::json;
DataPublisher* DataPublisher::ptrInstance = NULL;
string DataPublisher::m_address = "";

DataPublisher* DataPublisher::GetInstance(string address,bool isXPub) {
	if (!ptrInstance && m_address!=address) {
		ptrInstance = new DataPublisher(address,isXPub);
	}
	return ptrInstance;
}

DataPublisher::DataPublisher(string address,bool isXPub) {

	ctx = zmq_ctx_new();
	publisher = zmq_socket(ctx, ZMQ_PUB);
	int rc = -1;
	if (isXPub)
	{
		rc = zmq_connect(publisher, address.c_str());
	}
	else
	{
		rc = zmq_bind(publisher, address.c_str());
	}

	if (rc != 0)
	{
		LOG_ERROR<<"Can not connected:" + address;
	}
	m_address = address;
}

/*
* Notice: 
*1. If topic is empty string ,then all subscriber can get message
*2. If topicA name contain topicB name ,then subscriber B can get topicA message
*   so absolute different topic name is very important 
*/
void DataPublisher::SendMsg(char* data, int length, string topic) {
	if (topic != "")
	{
		zmq_send(publisher, topic.c_str(), topic.length(), ZMQ_SNDMORE);
	}
	zmq_send(publisher, data, length, 0);
}

DataPublisher::~DataPublisher() {
	zmq_close(publisher);
	zmq_ctx_destroy(ctx);
	delete ptrInstance;
}