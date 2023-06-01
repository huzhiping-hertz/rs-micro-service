#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "SNMPRequest.h"


class SNMPRequestSet {
protected :
	std::vector<SNMPRequest*> _requests;
public:	
	SNMPRequestSet();	
	virtual ~SNMPRequestSet();

	void addRequest(SNMPRequest * request);
	int getRequestCount()			{ return (int)_requests.size(); }
	SNMPRequest * getRequest(int i)	{ return _requests[i]; }
	void clear();

	void execute(SNMPRemoteAgent * pRemoteAgent = NULL);
	void cancel();
	void wait(DWORD timeout = INFINITE);

	bool isTerminated();

	std::string getDisplayInformation() const;
};
