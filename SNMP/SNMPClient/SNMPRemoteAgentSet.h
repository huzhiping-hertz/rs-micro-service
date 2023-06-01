#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "SNMPRemoteAgent.h"


class SNMPRemoteAgentSet {
protected :
	std::vector<SNMPRemoteAgent*> _agents;
public:	
	SNMPRemoteAgentSet();	
	virtual ~SNMPRemoteAgentSet();

	void addAgent(std::string name, std::string community, unsigned int port = 0, SNMPSession * pSession = NULL);
	int getAgentCount()			{ return (int)_agents.size(); }
	SNMPRemoteAgent * getAgent(int i)	{ return _agents[i]; }
	void clear();

	std::string getDisplayInformation() const;
};
