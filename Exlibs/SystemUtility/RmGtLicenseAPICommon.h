#ifndef RmGtLicenseAPICommon_H
#define RmGtLicenseAPICommon_H

#include <iostream>
#include <Windows.h>
#include "string.h"
#include <assert.h>
#include "RmGtLicenseAPIParams.h"

using namespace std;

//#define RM_GT_CPP_LOG_ENABLE		1

extern RmLicenseGeneralConfig gLicenseConfig;
extern void InitLicenseGeneralConfig(string rmRuntimeFolderPath, RmLicenseGeneralConfig& generalConfig);
extern void LicenseCheckStatus(string TestFunctionName, int Status);

const string gRmLicenseRuntimeFolderPath = "C:\\RMGT\\";
const string gRmLicenseDefaultFolderPath = "C:\\TestData\\";

extern const string gLicenseSdkDllPath;

extern const string gLicenseManagementDllPath;
extern const string gNewtonJsDllPath;


#endif
