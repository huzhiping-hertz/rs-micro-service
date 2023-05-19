#ifndef		LteUtility_H
#define		LteUtility_H

#include	<iostream>
#include	"SystemUtility.h"
#include	"string.h"
#include	"LTE_Coef_Head.h"

using namespace std;

extern int gLteStatusCode;
extern vector<float> gLteWinCof_4096;
extern vector<float> gLteWinCof_16384;

class  LteUtility
{
public:
	static string GetConfigureFolderPath();
	static string GetWinCoefFilePath(string fileName);
	static bool GetWinCoefData(int dutIndex, string fileName, vector<float> &winData);
	static bool GetWinCoefData(int dutIndex, int fftSize, vector<float> &winData);
};
#endif