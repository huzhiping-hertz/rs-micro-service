#define _CRT_SECURE_NO_WARNINGS

#ifndef SystemFileService_H
#define SystemFileService_H


#include	<sstream>
#include	"SystemUtility.h"
#include	<algorithm> // std::transform
#include	<string>
#include	<cctype> // std::toupper

class SystemFileService
{
public:
#if false
	//Bin File
	bool WriteToBinFile(string fileFullPath, byte *pbuffer, int nFileTotalSize);
	bool WriteToBinFile(string fileFullPath, int *pbuffer, int nFileTotalSize);
	bool WriteToBinFile(string fileFullPath, int16_t *pbuffer, int nFileTotalSize);
#endif
	template<class Type>
	bool WriteToBinFile(string fileFullPath, Type *pbuffer, int nFileTotalSize);

	int  GetBufferSize(string fileFullPath, int rwUnitSize);

	template<class Type>
	bool ReadFromBinFile(string fileFullPath, int rwUnitSize, Type *pBuffer, int nBufferSize);

	template<class Type>
	bool DisplayDataByGroup(Type *pBuffer, int nBufferSize, int nNumberInGroup);

	//CSV File
	bool OutputCsvFetchResult(vector<vector<string>> strArray);
	bool ReadFromCsvFile(string fileFullPath, vector<vector<string>> &strArray);
	bool FechDataFromCsvFile(string fileFullPath, vector<vector<string>> &strArray);
	long GetFileTotalSize(string fileFullPath);
	int GetDataFileRwUnitSize(string fileFullPathName);
private:
	char m_msgFmt[FILE_NAME_LENGTH];

};

template<class Type>
bool SystemFileService::ReadFromBinFile(string fileFullPath, int rwUnitSize, Type *pBuffer, int nBufferSize)
{
	bool bReturn = true;
	Type data = 0;
	ifstream fIn(fileFullPath, ios::in | ios::binary);
	int i = 0;

	if (fIn.is_open())
	{
		while (fIn.peek() != EOF)
		{
			fIn.read((char*)&data, sizeof(Type));

			if (i >= nBufferSize)
			{
				bReturn = false;

				Log(LOG_LEVEL_ERROR, "ReadFromBinFileCompairDouble index exceed the buffer size!");

				break;
			}

			pBuffer[i++] = data;
		}

		fIn.close();
	}
	else
	{
		bReturn = false;
	}

	return bReturn;
}

template<class Type>
bool SystemFileService::DisplayDataByGroup(Type *pBuffer, int nBufferSize, int nNumberInGroup)
{
	bool bReturn = true;
	int i = 0;
	int groupIndex = 0;
	string msgInGroup;

	do
	{
		if (i > nBufferSize - 1)
		{
			break;
		}

		msgInGroup = "Group Index = " + to_string(groupIndex);

		for (int j = 0; j < nNumberInGroup; j++)
		{
			msgInGroup += " Data" + to_string(j) + ",";
		}

		msgInGroup += " ";

		for (int j = 0; j < nNumberInGroup; j++)
		{
			msgInGroup += to_string(pBuffer[i++]) + ",";
		}

		sprintf(m_msgFmt, "%s", msgInGroup.c_str());

		Log(LOG_LEVEL_DEBUG, m_msgFmt);

		groupIndex++;
	} while (1);

	return bReturn;
}

template<class Type>
bool SystemFileService::WriteToBinFile(string fileFullPath, Type *pbuffer, int nFileTotalSize)
{
	bool bReturn = false;
	ofstream fileOut;

	fileOut.open(fileFullPath, std::ios::out | std::ios::binary);

	if (fileOut.is_open())
	{
		fileOut.write((char *)pbuffer, nFileTotalSize);

		fileOut.close();

		bReturn = true;

		sprintf(m_msgFmt, "WriteToBinFile file path = %s", fileFullPath.c_str());

		Log(LOG_LEVEL_INFOR, m_msgFmt);

		int unitSize = sizeof(Type);
		string typeName = typeid(Type).name();

		sprintf(m_msgFmt, "WriteToBinFile file size = %d , RwUnitSize = %d,Type Name = %s ", nFileTotalSize, unitSize, typeName.c_str());

		Log(LOG_LEVEL_INFOR, m_msgFmt);

	}
	else
	{
		char msgFmt[FILE_NAME_LENGTH];

		sprintf(msgFmt, "WriteToBinFile open file failed %s", fileFullPath.c_str());

		Log(LOG_LEVEL_ERROR, msgFmt);
	}

	return bReturn;
}








#endif
