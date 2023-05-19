#define _CRT_SECURE_NO_WARNINGS

#ifndef SystemCommonService_H
#define SystemCommonService_H


#include	<sstream>
#include	"SystemUtility.h"
#include	"SystemFileService.h"

class SysteCommonService
{
public :
	SysteCommonService();
	~SysteCommonService();
	void SetSimulationMode(bool mode);
	bool IsSimulationMode();

	int  GetBufferSize(string fileFullPath, int rwUnitSize);
	string GetExeFilePath(void);
	double GetSampleTimeMs(string fileFullPath, double sampleRateM);
	void ReplaceFilePath(char* filePath);

	template<class Type>
	bool WriteToBinFile(string fileFullPath, Type *pBuffer, int nFileTotalSize);

	template<class Type>
	bool ReadFromBinFile(string fileFullPath, int rwUnitSize, Type *pBuffer, int nBufferSize);
	
	template<class Type>
	bool DisplayDataByGroup(Type *pBuffer, int nBufferSize, int nNumberInGroup);
	
	void StrSplit(string str, const char split, vector<string>& res);
#ifdef _WIN32
	//CSV File
	bool SysteCommonService::OutputCsvFetchResult(vector<vector<string>> strArray);

	bool SysteCommonService::ReadFromCsvFile(string fileFullPath, vector<vector<string>> &strArray);
	bool SysteCommonService::FechDataFromCsvFile(string fileFullPath, vector<vector<string>> &strArray);
#endif
private:
	bool m_SimulationMode;
	SystemFileService m_FileService;

	char m_msgFmt[FILE_NAME_LENGTH];

	long GetFileTotalSize(string filePath);
	int GetDataFileRwUnitSize(string fileFullPathName);
	int GetFileLines(string filename);

	string& strReplaceAll(string& src, const string& old_value, const string& new_value);
};

template<class Type>
bool SysteCommonService::ReadFromBinFile(string fileFullPath, int rwUnitSize, Type *pBuffer, int nBufferSize)
{
	return m_FileService.ReadFromBinFile(fileFullPath, rwUnitSize, pBuffer, nBufferSize);
}

template<class Type>
bool SysteCommonService::DisplayDataByGroup(Type *pBuffer, int nBufferSize, int nNumberInGroup)
{
	return m_FileService.DisplayDataByGroup(pBuffer, nBufferSize, nNumberInGroup);
}


template<class Type>
bool SysteCommonService::WriteToBinFile(string fileFullPath, Type *pBuffer, int nBufferSize)
{
	return m_FileService.WriteToBinFile(fileFullPath, pBuffer, nBufferSize *sizeof(Type));
}








#endif
