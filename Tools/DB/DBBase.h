#ifndef DBBASE_H
#define DBBASE_H

#include "Poco/Data/Session.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/Data/SQLite/Connector.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::SessionPool;

namespace RS
{
	class DBBase
	{
	public:
		DBBase(){

		}

		static void Init()
		{
			//Poco::Data::SQLite::Connector::registerConnector();
			//Poco::Data::SQLite::Connector::enableSharedCache();
		}


		static void UnInit()
		{
			Poco::Data::SQLite::Connector::unregisterConnector();
		}

		static Session GetSession()
		{
			if (isInit == false)
			{
				Poco::Data::SQLite::Connector::registerConnector();
				Poco::Data::SQLite::Connector::enableSharedCache();
				isInit = true;
			}
			return pool.get();
		}

		static Session GetAopSession()
		{
			if (isAopInit == false)
			{
				Poco::Data::SQLite::Connector::registerConnector();
				Poco::Data::SQLite::Connector::enableSharedCache();
				isAopInit = true;
			}
			return aopPool.get();
		}
	protected:
		static bool isInit;
		static Poco::Data::SessionPool pool;
		static bool isAopInit;
		static Poco::Data::SessionPool aopPool;
	};
}

#endif