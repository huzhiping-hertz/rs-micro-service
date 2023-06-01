#include "DBBase.h"

using namespace RS;

bool DBBase::isInit = false;
bool DBBase::isAopInit = false;
Poco::Data::SessionPool DBBase::pool("SQLite", "mnsa.db");
Poco::Data::SessionPool DBBase::aopPool("SQLite", "mnsa.db");