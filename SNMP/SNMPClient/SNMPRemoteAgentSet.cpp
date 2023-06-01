#include "SNMPRemoteAgentSet.h"

#include <sstream>
#include <iostream>

#define __VER__ "1.0"


SNMPRemoteAgentSet::SNMPRemoteAgentSet() {
}

SNMPRemoteAgentSet::~SNMPRemoteAgentSet() {
	clear();
}

void SNMPRemoteAgentSet::clear() {
	while((int)_agents.size()) {
		delete _agents[0];
		_agents.erase(_agents.begin());
	}
}

void SNMPRemoteAgentSet::addAgent(std::string name, std::string community, unsigned int port, SNMPSession * pSession)
{
	_agents.insert(_agents.end(), new SNMPRemoteAgent(name, community, port, pSession));
}

std::string SNMPRemoteAgentSet::getDisplayInformation() const
{
	std::stringstream ss;
	ss << "Remote Agent Set: [";
	for(int i=0; i<(int)_agents.size(); i++) {
		ss << _agents[i]->getDisplayInformation();
		if(i < (int)_agents.size()-1) {
			ss << ", ";
		}
	}
	ss << "]";
	return ss.str();
}
