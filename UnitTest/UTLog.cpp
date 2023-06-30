#include "CommonUtility/NetUtility.h"
#include "CommonUtility/Loger.h"

#include "catch2/catch_all.hpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <string>

using namespace nlohmann;
using namespace RS;

TEST_CASE("Log", "[Log]")
{
    //Loger::InitLog("tester.log");
    Loger()<<"hello template"<<20;
    LOG_INFO <<"hello Macro"<<30;
}

TEST_CASE("LogInit", "[LogInit]")
{
    Loger::InitLog("tester.log");
    Loger()<<"hello template"<<20;
    LOG_INFO <<"hello Macro"<<30;
}