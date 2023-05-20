#include "LteDemodulation.h"
#include "Poco/Thread.h"

LteDemodulation::LteDemodulation(){}
LteDemodulation::~LteDemodulation() {}

string LteDemodulation::run(string params) {

  LOG_INFO << "Call Lte Demodulation ...";
  json paramObj = json::parse(params);
  Poco::Thread::sleep(10000);
  return "success run demodulation";
}

string LteDemodulation::getParams()
{
    LOG_INFO << "Get LTE demodulation parameters template...";
    json paramObj;

    paramObj["version"]="v1.0";
    paramObj["log"] = "/log/";
    paramObj["data"] = "/data/";

    return paramObj.dump();
}
