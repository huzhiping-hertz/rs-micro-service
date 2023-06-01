
#include "SNMPTrap.h"
#include "SNMPRemoteAgent.h"
#include "SNMPSession.h"
#include "SNMPObject.h"
#include "SNMPException.h"

#include <sstream>
#include <iostream>

#define __VER__ "1.0"


std::string SNMPTrap::getDisplayInformation() const
{
	std::stringstream ss;
	ss << "Trap: [" << _pattern << "]";
	return ss.str();
}

SNMPTrap * SNMPTrap::clone()
{
	SNMPTrap * myclone = new SNMPTrap(_pattern, _pRemoteAgent);
	return myclone;
}

SNMPTrap::SNMPTrap(std::string pattern, SNMPRemoteAgent * pRemoteAgent) {
	_registered = false;
	_pRemoteAgent = pRemoteAgent;
	_pattern = pattern;
	if(_pattern != "") {
		if(SnmpStrToOid(_pattern.c_str(), &_oidPattern) == SNMPAPI_FAILURE) {
			SNMP_THROW_ERROR("Could not convert OID from string representation", SnmpGetLastError(NULL), SNMP_ERROR);
		}
	}
}

SNMPTrap::~SNMPTrap()
{
	disable();
	if(_pattern != "") {
		SnmpFreeDescriptor(SNMP_SYNTAX_OCTETS, (smiLPOPAQUE)&_oidPattern);
	}
}

void SNMPTrap::disable()
{
	_registered = false;
	if(!_pRemoteAgent || !_registered) {
		return;
	}
	SNMPSession * session = _pRemoteAgent->getSession();
	smiLPCOID notification = NULL;
	if(_pattern != "") {
		notification = &_oidPattern;
	}
	if(SNMPTRACEAENABLED()) {
		std::stringstream trace;
		trace << "trap off < " << _pRemoteAgent->getName() << " " << _pRemoteAgent->getCommunity() << " " << _pattern;
		SNMPTRACE(trace.str());
	}
	if(SNMPAPI_SUCCESS != SnmpRegister(	session->getHandle(),
										NULL,
										_pRemoteAgent->getCommunityHandle(),
										_pRemoteAgent->getContextHandle(),
										notification,
										SNMPAPI_OFF)) {
		SNMP_THROW_ERROR("Could not unregister trap", SnmpGetLastError(session->getHandle()), SNMP_ERROR);
	}
}

void SNMPTrap::enable(SNMPRemoteAgent * pRemoteAgent) {
	if(pRemoteAgent != _pRemoteAgent) {
		disable();
		if(pRemoteAgent != NULL) {
			_pRemoteAgent = pRemoteAgent;
		}
	}
	if(!_pRemoteAgent || _registered) {
		return;
	}
	SNMPSession * session = _pRemoteAgent->getSession();
	smiLPCOID notification = NULL;
	if(_pattern != "") {
		notification = &_oidPattern;
	}
	if(SNMPTRACEAENABLED()) {
		std::stringstream trace;
		trace << "trap on < " << _pRemoteAgent->getName() << " " << _pRemoteAgent->getCommunity() << " " << _pattern;
		SNMPTRACE(trace.str());
	}
	if(SNMPAPI_SUCCESS != SnmpRegister(	session->getHandle(),
										NULL,
										_pRemoteAgent->getCommunityHandle(),
										_pRemoteAgent->getContextHandle(),
										notification,
										SNMPAPI_ON)) {
		SNMP_THROW_ERROR("Could not register trap", SnmpGetLastError(session->getHandle()), SNMP_ERROR);
	}
}

