#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "SNMPObject.h"

class SNMPSession;
class SNMPRemoteAgent;
class SNMPRequest;
class SNMPRequestSet;
class SNMPTrap;

class SNMPRemoteAgent {
	friend class SNMPSession;
	friend class SNMPRequest;
	friend class SNMPRequestSet;
	friend class SNMPTrap;
protected:
	std::string _name;
	std::string _community;
	UINT _port;
	bool _bInit;
	bool _mySession;
	SNMPSession * _pSession;
	HSNMP_ENTITY _hEntity;
	HSNMP_CONTEXT _hContext;

	HSNMP_ENTITY getCommunityHandle() { return _hEntity; }
	HSNMP_CONTEXT getContextHandle() { return _hContext; }
	SNMPSession * getSession() { return _pSession; }

	std::map<int,SNMPRequest*> _requestMap;
	void addToRequestMap(int id, SNMPRequest* pRequest) { _requestMap[id] = pRequest; }
	void removeFromRequestMap(int id) { 
		_requestMap.erase(id); 
	}
	SNMPRequest* getRequest(int id);
    
	void sendRequest(SNMPRequest * pRequest);
	void cancelRequest(int id);

public:	
	SNMPRemoteAgent(std::string name, std::string community, unsigned int port = 0, SNMPSession * pSession = NULL);
	~SNMPRemoteAgent();

	std::string	getName() { return _name; }
	std::string	getCommunity() { return _community; }

	virtual std::string getDisplayInformation() const;
};


