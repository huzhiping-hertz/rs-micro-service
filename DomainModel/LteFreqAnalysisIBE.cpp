#include "LteFreqAnalysisIBE.h"
#include "Poco/Thread.h"

// #include "SystemUtility.h"
// #include "LteUlDll.h"

LteFreqAnalysisIBE::LteFreqAnalysisIBE()
{
	
}
LteFreqAnalysisIBE::~LteFreqAnalysisIBE()
{
}

string LteFreqAnalysisIBE::getParams()
{
	LOG_INFO << "Get frequency analysis parameters template...";
    json paramObj;

	paramObj["version"]="v1.0";
    paramObj["log"] = "/log/";
    paramObj["data"] = "/data/";
    paramObj["SampleRate"] = (float)122.88;
    paramObj["SampleTime"] = 5;
    paramObj["BW"] = "LTE_BW_20M";
    paramObj["Numerlogy"] = "LTE_SC_INTERVAL_15_KHz";
    paramObj["RBNum"] = 100;
    paramObj["RBoffset"] = 0;
    paramObj["CenertFreq"] = (float)3.424995e9;
    paramObj["FreqDomainMeasureType"] = "LTE_UL_MEASURE_IBE";

    return paramObj.dump();
}

string LteFreqAnalysisIBE::run(string params)
{
	LOG_INFO << "Call FreqAnalysis...";
	json paramObj = json::parse(params);
	Poco::Thread::sleep(10000);
	return "success run analysis";
	// int DutIndex = 0;
	// int logToMode = LOG_TO_CONSOLE | LOG_TO_FILE;
	// int logLevel = LOG_LEVEL_DEBUG;

	// LteUlIbeInParam* pIbeInParams = new LteUlIbeInParam();
	// LteUlIbeOutParam* pIbeOutParams = new LteUlIbeOutParam();

	// string logPath = paramObj["log"].get<string>();
	// string iqData = paramObj["data"].get<string>();

	// LogInitByDutIndex(DutIndex, logToMode, logLevel, (char*)logPath.c_str(), "LteUlFreqAnalysisLogFile", true);
	// //LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("TestLteUlIbe Start!"));
	// LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, "TestLteUlIbe");
	
	// DllLteUlLibEnter(DutIndex);
	// DllLteUlIbeInitDefaut(DutIndex, pIbeInParams);
	// memcpy(pIbeInParams->IqDataPath, (char*)iqData.c_str(), iqData.length());
	// memcpy(pIbeInParams->BinFileLogFolder, (char*)logPath.c_str(), logPath.length());
	// pIbeInParams->SampleRate = paramObj["SampleRate"].get<float>();
	// pIbeInParams->SampleTime = paramObj["SampleTime"].get<float>();
	// pIbeInParams->BW = paramObj["BW"].get<int>();
	// pIbeInParams->Numerlogy = paramObj["Numerlogy"].get<int>();
	// pIbeInParams->RBNum = paramObj["RBNum"].get<int>();
	// pIbeInParams->RBoffset = paramObj["RBoffset"].get<int>();
	// pIbeInParams->CenertFreq = paramObj["CenertFreq"].get<float>();
	// pIbeInParams->FreqDomainMeasureType = paramObj["FreqDomainMeasureType"].get<int>();;
	// DllLteUlIbeTest(DutIndex, pIbeInParams, pIbeOutParams);

	// DllLteUlLibExit(DutIndex);
	// LogCleaupByDutIndex(DutIndex);

	// delete pIbeInParams;
	// delete pIbeOutParams;
}
