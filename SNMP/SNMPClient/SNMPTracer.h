#pragma once 

#include "Winsnmp.h"
#include <string>

#define SNMPTRACE(a)		SNMPTracer::getTracer()->trace(a)
#define SNMPTRACEAENABLED()	SNMPTracer::getTracer()->isEnabled()

class SNMPTracer {
protected:	
	static SNMPTracer _snmpTracer;
	
    HANDLE _hConsole;
	HANDLE _hConsoleInput;
	bool _active;

	SNMPTracer();
	~SNMPTracer();
	
public:
	static SNMPTracer * getTracer() { return &_snmpTracer; }

	void enable(bool on) { _active = on; }
	bool isEnabled() const { return _active; }
	void trace(const std::string & message);
};


