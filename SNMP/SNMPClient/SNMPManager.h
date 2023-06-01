#pragma once 

#include "Winsnmp.h"
#include "SNMPSession.h"
#include <map>


class SNMPManager {

friend class SNMPSession;
friend class SNMPRequest;
friend class SNMPRemoteAgent;

protected:
	static SNMPManager _snmpManager;
	
	static std::string pduTypeToStr(int type);
	static std::string pduErrorToStr(int error);	
	static std::string pduToStr(	HSNMP_ENTITY hDstEntity,
									HSNMP_ENTITY hSrcEntity,
									HSNMP_CONTEXT hContext,
									smiINT32 pduType,
									smiINT32 pduId,
									smiINT32 pduError,
									HSNMP_VBL hVbl,
									bool leftToRight = true);

	bool _init;
	smiUINT32 _nMajorVersion;
	smiUINT32 _nMinorVersion;
	smiUINT32 _nLevel;
	
	SNMPManager();
	~SNMPManager();
	void cleanUp();
	
	std::map<HSNMP_SESSION,SNMPSession*> _sessions;
	void unregisterSession(SNMPSession * session);
	void registerSession(SNMPSession * session); 
	SNMPSession * getSession(HSNMP_SESSION handle);

public:
	static SNMPManager * getManager() { return &_snmpManager; }

	void startup();
	std::string getDisplayInformation() const;
};


