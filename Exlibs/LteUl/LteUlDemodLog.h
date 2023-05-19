#ifndef LteUlDemodLog_H
#define LteUlDemodLog_H

#include	"LteUlInputParam.h"
#include	"ComParaAndFun.h"

class LteUlDemodLog
{
	public :
		void LogInputParam(LteUlInputParam *pInputParams);
		void LogOutputResult(LteUlOutputParam *pOutputParam);

		void WriteFreqPowerDataToBinFile(LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam, vector<float> PowerListdBm, vector<float> freqList);
		int OutputResultToFile(LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);
		int DutIndex;
	private:
		char m_msgFormat[FILE_NAME_LENGTH];

		void LogInputGeneralParam(LteUlInputParam *pInputParams);

		void LogInputCellParam(LteUlInputParam *pInputParams);

		int LogInputDmrsParam(LteUlInputParam *pInputParams);

		int GetFreqDomainAnalysisResult(LteUlInputParam *pInputParam, vector<float> PowerListdBm, vector<float> freqList, float *pBuffer, int buffersize);
		void WriteFreqPowerToFile(float *pbuffer, int nbufferLength, LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);

		void GetOutputResultFileFullPath(LteUlInputParam *pInputParam, string &fileFullPath);

};

#endif
