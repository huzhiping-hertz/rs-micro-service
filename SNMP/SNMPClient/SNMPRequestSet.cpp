
#include "SNMPRequestSet.h"
#include "SNMPRemoteAgent.h"
#include "SNMPSession.h"
#include "SNMPObject.h"
#include "SNMPException.h"

#include <sstream>
#include <iostream>

#define __VER__ "1.0"


SNMPRequestSet::SNMPRequestSet() {
}

SNMPRequestSet::~SNMPRequestSet() {
	clear();
}

void SNMPRequestSet::clear() {
	while((int)_requests.size()) {
		delete _requests[0];
		_requests.erase(_requests.begin());
	}
}

void SNMPRequestSet::addRequest(SNMPRequest * request)
{
	_requests.insert(_requests.end(), request->clone());
}

void SNMPRequestSet::execute(SNMPRemoteAgent * pRemoteAgent)
{
	for(int i=0; i<(int)_requests.size(); i++) {
		_requests[i]->execute(pRemoteAgent);
	}
}

void SNMPRequestSet::cancel()
{
	for(int i=0; i<(int)_requests.size(); i++) {
		_requests[i]->cancel();
	}
}


void SNMPRequestSet::wait(DWORD timeout)
{
	int count = (int)_requests.size();
	SNMPRequest ** requests = new SNMPRequest*[count];
	HANDLE * events = new HANDLE[count];
	int cnt = 0;
	int i;
	for(i=0; i<count; i++) {
		requests[cnt] = _requests[i];
		events[cnt] = requests[cnt]->_hWait;
		cnt++;
	}
	if(cnt > MAXIMUM_WAIT_OBJECTS) {
		delete [] events;
		delete [] requests;
		SNMP_THROW_ERROR("Cannot wait for that many requests", SNMPAPI_OTHER_ERROR, SNMP_ERROR);
    }
	DWORD waitRet = ::WaitForMultipleObjects(cnt, events, TRUE, timeout);
	for(i=0; i<cnt; i++) {
		::ResetEvent(requests[i]->_hWait);
		// _state, _error and result set by WinSNMP!
		requests[i]->_pRemoteAgent->cancelRequest(requests[i]->_requestId);
		SnmpFreePdu(requests[i]->_hPdu);
		SnmpFreeVbl(requests[i]->_hVbl);
		if(waitRet == WAIT_FAILED) {
			requests[i]->_state = SNMP_RAREQ_STATE_ERROR;
			requests[i]->_error = SNMP_ERROR_GENERR;
		}
		if(requests[i]->_state == SNMP_RAREQ_STATE_ONGOING) {
			requests[i]->_state = SNMP_RAREQ_STATE_TIMEDOUT;
			requests[i]->_error = SNMP_ERROR_NOERROR;
			if(SNMPTRACEAENABLED()) {
				std::stringstream trace;
				trace << "rx < timeout(" << requests[i]->_requestId << ", " << timeout << ")";
				SNMPTRACE(trace.str());
			}
		}
		requests[i]->_requestId = 0;
	}
	delete [] events;
	delete [] requests;
	if(waitRet == WAIT_FAILED) {
		SNMP_THROW_ERROR("Wait failed", SNMPAPI_OTHER_ERROR, SNMP_ERROR);
	}
}

bool SNMPRequestSet::isTerminated()
{
	bool terminated = true;
	for(int i=0; i<(int)_requests.size(); i++) {
		terminated &= _requests[i]->isTerminated();
	}
	return terminated;
}

std::string SNMPRequestSet::getDisplayInformation() const
{
	std::stringstream ss;
	ss << "Request Set: [";
	for(int i=0; i<(int)_requests.size(); i++) {
		ss << _requests[i]->getDisplayInformation();
		if(i < (int)_requests.size()-1) {
			ss << ", ";
		}
	}
	ss << "]";
	return ss.str();
}
