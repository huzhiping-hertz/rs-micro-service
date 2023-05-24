#include "CommonUtility/NetUtility.h"
#include "catch2/catch_all.hpp"
#include "nlohmann/json.hpp"
#include "trantor/utils/Logger.h"
#include "trantor/utils/AsyncFileLogger.h"
#include <iostream>
#include <string>

using namespace nlohmann;

TEST_CASE("LogConsole", "[LogConsole]")
{

  LOG_INFO << "This is a info test";
  LOG_ERROR << "This is a error test";

}

TEST_CASE("LogFile", "[LogFile]")
{
    trantor::AsyncFileLogger fileLoger;
    fileLoger.setFileName("logfile");
    fileLoger.startLogging();
    trantor::Logger::setOutputFunction(
        [&](const char *msg, const uint64_t len) {
            fileLoger.output(msg, len);
        },
        [&]() { fileLoger.flush(); });
    fileLoger.setFileSizeLimit(10000000);

    LOG_ERROR << "this is the "  << "file log ";
}