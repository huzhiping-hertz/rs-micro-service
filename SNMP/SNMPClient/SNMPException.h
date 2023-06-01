#pragma once 

#include "Winsnmp.h"
#include <string>
#include <sstream>

#include "SNMPTracer.h"

#define SNMP_THROW_BASE(e) { SNMPException * psnmpe = e; SNMPTRACE(psnmpe->toString()); throw psnmpe; }

#define SNMP_THROW_EXCEPTION(message) SNMP_THROW_BASE(new SNMPException(message, NULL, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))
#define SNMP_RETHROW_EXCEPTION(message, exception) SNMP_THROW_BASE(new SNMPException(, exception, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))

#define SNMP_THROW_ERROR(message, number, level) SNMP_THROW_BASE(new SNMPErrorException(number, level, message, NULL, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))
#define SNMP_RETHROW_ERROR(message, exception, number, level) SNMP_THROW_BASE(new SNMPErrorException(number, level, message, exception, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))


class SNMPException {
protected:
	std::string _message;
	std::string _source;
	SNMPException * _previous;
public:
	SNMPException(	std::string message = "", 
					SNMPException * prev = NULL, 
					const char * file = NULL, 
					int line = 0, 
					const char * date = NULL,
					const char * time = NULL, 
					const char * ver = NULL);
	virtual ~SNMPException();
	virtual std::string toString();
	virtual std::string toStringStack();
};


#define SNMP_ERROR		0
#define SNMP_WARNING	1


class SNMPErrorException : public SNMPException {
protected:
	int _level;
	int _number;
public:
	SNMPErrorException(int number = SNMPAPI_OTHER_ERROR, int level = SNMP_WARNING, std::string message = "", SNMPException * prev = NULL, const char * file = NULL, int line = 0, const char * date = NULL, const char * time = NULL, const char * ver = NULL);	
	virtual ~SNMPErrorException();
	virtual std::string toString();
};



