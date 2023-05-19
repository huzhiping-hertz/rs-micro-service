#ifndef SystemUtility_H
#define SystemUtility_H


#include	<ctime>
#include	<iostream>
#include	<string>
#include	<vector>
#include	<fstream>
#include	<cstring>
#include	<complex>
#include	"DspCommonTypeDefine.h"
#include	<stdint.h>

#ifdef _WIN32
#include	<windows.h>
#define STDCALL					__stdcall
#define DLLEXPORT				__declspec(dllexport)
#else
#define DLLEXPORT	
#endif

typedef std::complex<double> complex_t;
using namespace std;

#define LOG_TO_CONSOLE				0x1
#define LOG_TO_FILE					0x2
#define LOG_TO_FILE_AND_CONSOLE		0x3

#define FILE_NAME_LENGTH 256

#ifdef _WIN32
#define RM_DSP_DEFULAT_FOLDER_PATH	"C:\\TestData\\DSP\\"
#else
#define RM_DSP_DEFULAT_FOLDER_PATH	"/home/rm/CPP/TestData/DSP/"
#endif

#define LOG_LEVEL_RD		0
#define LOG_LEVEL_DEBUG		1
#define LOG_LEVEL_INFOR		2
#define LOG_LEVEL_NORMAL	3
#define LOG_LEVEL_WARNING	4
#define LOG_LEVEL_ERROR		5

#define OUT_MODE_RESULT		0x01
#define OUT_MODE_BIN_FILE	0x02
#define OUT_MODE_BUFFER		0x04

#define RM_INPUT_FROM_FILE		0
#define RM_INPUT_FROM_BUFFER	1

#define DUPLEX_MODE_TDD		0
#define DUPLEX_MODE_FDD		1

#define RMSA_MODULATION_AUTO		0
#define RMSA_MODULATION_BPSK		1
#define RMSA_MODULATION_QPSK		2
#define RMSA_MODULATION_16QAM		3
#define RMSA_MODULATION_64QAM		4
#define RMSA_MODULATION_256QAM		5
#define RMSA_MODULATION_1024AM		6

#define MAX_DUT_NUMBER 4

#define UNIT_M		1e6
#define UNIT_KILO	1e3
#define	MHZ_TO_HZ	1e6

#define INVALID_NEG_VALUE  -999.0
#define LOG_SAVE_NUMBER		100

#define FILE_TYPE_BIN	0
#define FILE_TYPE_CSV	1
#define FILE_TYPE_TXT	2
#define FILE_TYPE_AWF	3

#define RM_ENABLE		1
#define RM_DISABLE		0

struct BinFileTestObject
{
	double real;
	double image;
} ;

struct BinFileInfor
{
	//InputParam
	char inputfileFullPath[FILE_NAME_LENGTH];
	char outputFileFolder[FILE_NAME_LENGTH];
	char outputFileName[FILE_NAME_LENGTH];

	double sampleRate;
	double sampleTime;

	int totalLength;// the total Byte number
	int	rwSizeUnit;
	int captureLength;

	int extractFactor;
	int extractLength;

	//OutputParam
	char outputFileFullPath[FILE_NAME_LENGTH];
};


struct SysEnvironment
{
	char* WorkPath;
};

/// <summary>
/// RM License related structure
/// </summary>
/// 
struct RmLicenseResult
{
	string LicenseValidDate;
	string LicenseGenDate;
	int LicenseDays;
	int RemainingDays;
	string LicenseFilePath;
	bool IsLicensed;
	string ErrMsg;
	string LicenseType;
	string LicenseStateMsg;
};

#ifdef _WIN32
extern "C" int STDCALL LogInit(int logToMode, int logLevel, char *folderPath,char* fileName);
extern "C" int STDCALL LogInitCreatedByDay(int logToMode, int logLevel, char *folderPath, char* fileName);
extern "C" int STDCALL Log(int logLevel, char* msg);
extern "C" int STDCALL LogCleaup();
extern "C" int STDCALL GetSystemLocalTime(char *pLocalTime);

extern "C" int STDCALL LogInitByDutIndex(int dutIndex, int logToMode, int logLevel, char *folderPath, char* fileName, bool createdByDay = false);
extern "C" int STDCALL LogByDutIndex(int dutIndex, int logLevel, char* msg);
extern "C" int STDCALL LogCleaupByDutIndex(int dutIndex);

extern "C" int STDCALL LogFloatByDutIndex(int dutIndex,int logLevel, const char* msg, float value);
extern "C" int STDCALL LogIntByDutIndex(int dutIndex,int logLevel, const char* msg, int value);
extern "C" int STDCALL LogStrByDutIndex(int dutIndex, int logLevel, const char* msg, const char* value);
extern "C" int STDCALL LogComplexByDutIndex(int dutIndex, int logLevel, const char* msg, complex_t value);
extern "C" int STDCALL LogBoolByDutIndex(int dutIndex, int logLevel, const char* msg, bool value);

extern "C" int STDCALL WriteToBinFileSample(char* folderPath,BinFileInfor *fileInfor);
extern "C" int STDCALL ReadFromBinFileSample(BinFileInfor *fileInfor);
extern "C" bool STDCALL GetLogFileName(string &fileFullPath, string folderPath, char* fileName, string postFix,bool createdByDay = false);
extern "C" bool STDCALL GetLogFileNameWithTimeStamp(string &fileFullPath, string folderPath, char* fileName, string postFix,bool bUseTimeStamp);
extern "C" bool STDCALL IsLogDebugLevel();
extern "C" bool STDCALL IsLogDebugLevelByDutIndex(int dutIndex);
extern "C" bool STDCALL IsSimulationModeDll();
extern "C" void STDCALL SetSimulationModeDll(bool mode);
extern "C" bool STDCALL IsLogRDLevel(int dutIndex);
extern "C"  int STDCALL GetLogLevel(int dutIndex);
extern "C" void STDCALL ReplaceFilePathDll(char* filePath);
extern "C" void STDCALL StrSplitDll(string str, const char split, vector<string>& res);

extern "C" bool STDCALL WriteToBinFileByteDll(string fileFullPath, BYTE *pbuffer, int nBufferSize);
extern "C" bool STDCALL WriteToBinFileIntDll(string fileFullPath, int *pbuffer, int nBufferSize);
extern "C" bool STDCALL WriteToBinFileInt16Dll(string fileFullPath, int16_t *pbuffer, int nBufferSize);
extern "C" bool STDCALL WriteToBinFileFloatDll(string fileFullPath, float *pbuffer, int nBufferSize);

extern "C" int STDCALL GetBufferSizeDll(string fileFullPath, int rwUnitSize);
extern "C" bool STDCALL ReadFromBinFileDoubleDll(string fileFullPath, int rwUnitSize, double *pBuffer, int nBufferSize, int nNumberInGroup);
extern "C" bool STDCALL ReadFromBinFileFloatDll(string fileFullPath, int rwUnitSize, float *pBuffer, int nBufferSize, int nNumberInGroup);

extern "C" bool STDCALL ReadFromCsvFileDll(string fileFullPath, vector<vector<string>> &strArray);

extern int GetSystemLocalTime(string &localTime,bool createdByDay =false);

extern "C" int STDCALL LogFloat(int logLevel, const char* msg, float value);
extern "C" int STDCALL LogInt(int logLevel, const char* msg, int value);
extern "C" int STDCALL LogStr(int logLevel, const char* msg, const char* value);
extern "C" int STDCALL LogComplex(int logLevel, const char* msg, complex_t value);
extern "C" int STDCALL LogFloatArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<float> vtArray);
extern "C" int STDCALL LogIntArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<int> vtArray);
extern "C" int STDCALL LogComplexArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<complex_t> vtArray);
extern "C" int STDCALL LogComplex2DArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<vector<complex_t> > vtArray);
extern "C" int STDCALL LogInt3DArrayToFile(int dutIndex, int logLevel, string fileFullPath, int *pArray, int iLength, int jLength, int kLength);

extern  string STDCALL GetExeFilePathDll();
extern  int STDCALL SetSystemEnvironmentDll(SysEnvironment *pSysEnvironememnt);
extern  int STDCALL GetSystemEnvironmentDll(SysEnvironment *pSysEnvironememnt);

extern  int STDCALL EnterRmCppSystemDll();
extern  int STDCALL ExitRmCppSystemDll();
extern int STDCALL GetSystemWorkPathDll(string &workPath);

extern bool STDCALL ReadIQDatafromFileDll_float(string filePath, int len, float *pIqData, float data);
extern bool STDCALL ReadIQDatafromFileDll_int16(string filePath, int len, int16_t *pIqData, int16_t data);
extern long STDCALL GetIqFileSampleNumberDll(char* iqFilePath, int rwUnitSize);

extern "C" int DLLEXPORT ByteArrayToFloatData(float externalloss, float factor, unsigned char * ByteArray, int ByteArrayLength, unsigned char * FloatByteArray, float * FloatArray, short * MaxAdcValue, short * OverLimitNumber);
extern "C" DLLEXPORT void  InitByteArray(unsigned char * InitArray, unsigned char InitValue, int InitLength);
extern "C" int STDCALL SetLogMaxLength(long maxLength);

extern "C" double STDCALL GetSampleTimeMsDll(char* path, double sampleRateM);
extern "C" int STDCALL LogSave(int dutIndex);
extern "C" int STDCALL SetLogRealTimeSaving(bool bEnable);

extern "C" bool STDCALL InitRmLicenseServiceDll();
extern "C" bool STDCALL IsSoftwareLicensedDll();
extern "C" RmLicenseResult STDCALL GetLicenseResultDll();
extern "C" bool STDCALL LogLicenseResult(RmLicenseResult licenseResult);
extern "C" bool STDCALL IsRmSoftwareLicensedDll();
#else //for OS_LINUX
extern "C"  int  LogInit(int logToMode, int logLevel, char *folderPath, char* fileName);
extern "C" int   LogInitCreatedByDay(int logToMode, int logLevel, char *folderPath, char* fileName);
extern "C"  int  Log(int logLevel, char* msg);
extern "C"  int  LogCleaup();
extern "C"  bool IsLogDebugLevel();
extern "C"  bool IsLogDebugLevelByDutIndex(int dutIndex);
extern "C"  int  WriteToBinFileSample(char* folderPath, BinFileInfor *fileInfor);
extern "C"  int  ReadFromBinFileSample(BinFileInfor *fileInfor);
extern "C"  bool GetLogFileName(string &fileFullPath, string folderPath, char* fileName, string postFix, bool createdByDay = false);
extern "C"  bool GetLogFileNameWithTimeStamp(string &fileFullPath, string folderPath, char* fileName, string postFix, bool bUseTimeStamp);

extern int  GetSystemLocalTime(string &localTime, bool createdByDay =false);
extern int GetDurationMs(timespec start, timespec end);

extern bool IsSimulationModeDll();
extern void SetSimulationModeDll(bool mode);
extern bool IsLogRDLevel(int dutIndex);
extern int  GetLogLevel(int dutIndex);
extern void ReplaceFilePathDll(char* filePath);
extern void StrSplitDll(string str, const char split, vector<string>&res);

extern "C"  int LogInitByDutIndex(int dutIndex, int logToMode, int logLevel, char *folderPath, char* fileName, bool createdByDay = false);
extern "C"  int LogByDutIndex(int dutIndex, int logLevel, char* msg);
extern "C"  int LogCleaupByDutIndex(int dutIndex);
extern "C" int LogFloatArrayToFile(int dutIndex, int logLevel,string fileFullPath, vector<float> vtArray);
extern "C" int LogIntArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<int> vtArray);
extern "C" int LogComplexArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<complex_t> vtArray);
extern "C" int LogComplex2DArrayToFile(int dutIndex, int logLevel, string fileFullPath, vector<vector<complex_t> > vtArray);
extern "C" int LogInt3DArrayToFile(int dutIndex, int logLevel, string fileFullPath, int *pArray, int iLength, int jLength, int kLength);

extern "C"  int  LogFloatByDutIndex(int dutIndex,int logLevel, const char* msg, float value);
extern "C"  int  LogIntByDutIndex(int dutIndex,int logLevel, const char* msg, int value);
extern "C"  int  LogStrByDutIndex(int dutIndex, int logLevel, const char* msg, const char* value);
extern "C"  int  LogComplexByDutIndex(int dutIndex, int logLevel, const char* msg, complex_t value);
extern "C"  int  LogBoolByDutIndex(int dutIndex, int logLevel, const char* msg, bool value);
extern  "C" bool WriteToBinFileByteDll(string fileFullPath, unsigned char *pbuffer, int nBufferSize);
extern  bool WriteToBinFileIntDll(string fileFullPath, int *pbuffer, int nBufferSize);
extern  bool WriteToBinFileInt16Dll(string fileFullPath, int16_t *pbuffer, int nBufferSize);
extern  bool WriteToBinFileFloatDll(string fileFullPath, float *pbuffer, int nBufferSize);

extern  int GetBufferSizeDll(string fileFullPath, int rwUnitSize);
extern  bool ReadFromBinFileDoubleDll(string fileFullPath, int rwUnitSize, double *pBuffer, int nBufferSize, int nNumberInGroup);
extern  bool ReadFromBinFileFloatDll(string fileFullPath, int rwUnitSize, float *pBuffer, int nBufferSize, int nNumberInGroup);

extern  bool ReadFromCsvFileDll(string fileFullPath, vector<vector<string>> &strArray);

extern  int LogFloat(int logLevel, const char* msg, float value);
extern  int LogInt(int logLevel, const char* msg, int value);
extern  int LogStr(int logLevel, const char* msg, const char* value);
extern  int LogComplex(int logLevel, const char* msg, complex_t value);

extern  int LogBoolByDutIndex(int dutIndex, int logLevel, const char* msg, bool value);

extern string GetExeFilePathDll();
extern  int SetSystemEnvironmentDll(SysEnvironment *pSysEnvironememnt);
extern  int GetSystemEnvironmentDll(SysEnvironment *pSysEnvironememnt);
extern  int EnterRmCppSystemDll();
extern  int ExitRmCppSystemDll();
extern	int GetSystemWorkPathDll(string &workPath);

extern bool ReadIQDatafromFileDll_float(string filePath, int len, float *pIqData, float data);
extern bool ReadIQDatafromFileDll_int16(string filePath, int len, int16_t *pIqData, int16_t data);
extern long GetIqFileSampleNumberDll(char* iqFilePath, int rwUnitSize);
extern "C"  int SetLogMaxLength(long maxLength);

extern double GetSampleTimeMsDll(char* path, double sampleRateM);
extern int LogSave(int dutIndex);
extern int SetLogRealTimeSaving(bool bEnable);
#endif

extern void WriteLogFile(int dutIndex, string msg);
extern void CreateLogFile(int dutIndex, char *folderPath, char* fileName, bool createdByDay = false);
extern bool OpenLogFile(int dutIndex, string filePath);

extern int GetLogMsg(int dutIndex, string &logMsg, string msg, int logLevel);
extern void OutputLog(int dutIndex, string logMsg);


#endif // header file