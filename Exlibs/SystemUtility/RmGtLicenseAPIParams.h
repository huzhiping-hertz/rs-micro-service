#ifndef RmGtLicenseAPIParams_H
#define RmGtLicenseAPIParams_H

#include <string>

using namespace std;

struct RmLicenseGeneralConfig
{
	//Customer Input params
	bool   DemoMode;
	bool   DspLogEnable;
	int	   UsbAddress;
	int    LogToMode;
	int	   LogLevel;
	bool   LogRealTimeSaving;
	bool   LogAntData;
	bool   CacheIQData;
	bool   BackupIQData;
	bool   ReloadArbFile;
	bool   LogResultEnable;

	string DllFolderPath;
	string LogFodlerPath;
	string DspAppFolderPath;
	string DspAppLogFolder;
	string RmGTVersion;
	string RmGTAPIVersion;

	string ConfigFolderPath;
	string ReportFolderPath;
};



enum ERmLicenseApiStatus
{
	RM_LICENSE_API_SUCCESS = 0,
};



#endif
