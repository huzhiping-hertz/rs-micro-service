#pragma once 

#include "Winsnmp.h"
#include <string>
#include <map>
#include "SNMPRemoteAgent.h"
#include "SNMPRequest.h"
#include "SNMPTrap.h"

class SNMPSession {

friend class SNMPRemoteAgent;
friend class SNMPManager;
friend class SNMPRequest;
friend class SNMPTrap;
friend SNMPAPI_STATUS CALLBACK snmpCallBackFunction( HSNMP_SESSION hSession, HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam, LPVOID lpClientData);

protected:
	HSNMP_SESSION _hSession;
	SNMPSession(HSNMP_SESSION hSession);
	void closeSession();

	std::map<HSNMP_CONTEXT,SNMPRemoteAgent*> _ragents;
	SNMPRemoteAgent * getRemoteAgent(HSNMP_CONTEXT handle);
	void unregisterRemoteAgent(SNMPRemoteAgent * ragent);
	void registerRemoteAgent(SNMPRemoteAgent * ragent); 
	SNMPAPI_STATUS processNotification(WPARAM wParam, LPARAM lParam);
	
	const HSNMP_SESSION getHandle() const { return _hSession; }
public:
	SNMPSession();
	~SNMPSession();
	
	virtual void processTrap(const SNMPObject & object) {}
};


