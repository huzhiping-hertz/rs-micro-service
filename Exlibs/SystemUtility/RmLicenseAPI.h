#ifndef RmLicenseAPI_H
#define RmLicenseAPI_H

#include	<iostream>
#include	<vector>
#include	"RmGtLicenseAPIParams.h"
#include	"RmGtLicenseAPICommon.h"


//#define RM_LICNESE_DEBUG_MODE			1
//#define RM_LICNESE_CSHARP_DLL_DEBUG		1

using namespace std;
using std::string;

class RmLicenseAPI
{
public:
	int CreateLicenseTester();
	bool InitRegisterService();
	bool RegisterLogService();
	bool IsSoftwareLicensed();
	void LogLicenseResult(RmLicenseResult result);
	RmLicenseResult GetLicenseResult();
private:
	int LoadLicenseDlls();
	void SaveExceptionLog(int status);
	
	int m_Status;
	int m_IntegritCode;
	int m_AppId;

	RmLicenseResult m_LicenseResult;
};

#endif