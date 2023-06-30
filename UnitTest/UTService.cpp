// #include "CommonUtility/NetUtility.h"
// #include "catch2/catch_all.hpp"
// #include "nlohmann/json.hpp"
// #include "trantor/utils/Logger.h"
// #include "trantor/utils/AsyncFileLogger.h"
// #include <iostream>
// #include <string>


// using namespace RM;
// using namespace std;
// using namespace nlohmann;


// TEST_CASE("LTE", "[LTE]") {

//   SECTION("204") {
//     string url = "http://127.0.0.1:8080/api/lte/analysis";
//     json paramObj;

//     string logPath = "C:\\TestData\\DSP\\LteUl\\Log\\204\\";
//     string iqData =
//         "C:\\TestData\\DSP\\LteUl\\IQData\\Fun204\\LTE_10M_FullRB_QPSK_EVM_"
//         "failed\\1\\IQDataCentral.float";

//     paramObj["log"] = logPath;
//     paramObj["data"] = iqData;
//     paramObj["DutIndex"] = 0;
//     // paramObj["SampleRate"] = (float)15.36;
//     // paramObj["SampleTime"] = (float)20.1;
//     // paramObj["UserCellID"] = 0;
//     // paramObj["UserRBOffset"] = 0;
//     // paramObj["UserRBNumber"] = 50;
//     // paramObj["UserDelta_ss"] = 0;
//     // paramObj["Usern_1_DMRS"] = 0;
//     // paramObj["Usern_2_DMRS"] = 0;
//     // paramObj["Userseq_hop_enabled"] = SEQ_HOP_DISABLED;
//     // paramObj["Usergroup_hop_enabled"] = GROUP_HOP_DISABLED;
//     // paramObj["UserBW"] = LTE_BW_10M;
//     // paramObj["UserDMRSBoostdB"] = 0;
//     // paramObj["UserModulation"] = LTE_MODULATION_QPSK;

//     map<string, string> headers;
//     //Loger::Trace("Start Call LTE Demodulation");
//     NetUtility::PostRequest(url, paramObj.dump(), headers);
//     //Loger::Trace("End Call LTE Demodulation");
//   }

//   SECTION("251") {
//     string url = "http://127.0.0.1:8011/api/lte/demodulate";
//     json paramObj;

//     string logPath = "C:\\TestData\\DSP\\LteUl\\Log\\251\\";
//     string iqData =
//         "C:\\TestData\\DSP\\LteUl\\IQData\\Fun251\\LTE20BW_122.88SR.float";

//     paramObj["log"] = logPath;
//     paramObj["data"] = iqData;
//     // paramObj["SampleRate"] = (float)122.88;
//     // paramObj["SampleTime"] = 5;
//     // paramObj["BW"] = LTE_BW_20M;
//     // paramObj["Numerlogy"] = LTE_SC_INTERVAL_15_KHz;
//     // paramObj["RBNum"] = 100;
//     // paramObj["RBoffset"] = 0;
//     // paramObj["CenertFreq"] = (float)3.424995e9;
//     // paramObj["FreqDomainMeasureType"] = LTE_UL_MEASURE_IBE;

//     map<string, string> headers;
//     //Loger::Trace("Start Call LTE Frequency Analysis");
//     NetUtility::PostRequest(url, paramObj.dump(), headers);
//     //Loger::Trace("End Call LTE Frequency Analysis");
//   }
// }