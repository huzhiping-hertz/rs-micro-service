#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "SNMPObject.h"


class SNMPSession;
class SNMPRemoteAgent;

class SNMPTrap {
	friend class SNMPRemoteAgent;
	friend class SNMPSession;
protected :
	std::string _pattern;
	smiOID _oidPattern;
	SNMPRemoteAgent * _pRemoteAgent;
	bool _registered;

public:	
	SNMPTrap(std::string pattern, SNMPRemoteAgent * pRemoteAgent);
	virtual ~SNMPTrap();

public:
	void enable(SNMPRemoteAgent * pRemoteAgent = NULL);
	void disable();

	SNMPTrap * clone();

	std::string getDisplayInformation() const;
};


