#ifndef LteUlDemodTest_H
#define LteUlDemodTest_H

#include	<string>
#include	<vector>
#include	<complex>
#include	"ComParaAndFun.h"
#include	"SystemUtility.h"
#include	<cstring>
#include	"LteUlDemodLog.h"
#include	"LteUlInputParam.h"
#include	"LteUlDemodParams.h"
#include	"LteUlDemodSync.h"
#include	"LteUlDemodFreqErrorHandler.h"
#include	"LteUlDemodEvmHandler.h"

using std::string;


 class LteUlDemodTest
{
public:
	LteUlDemodTest();
	~LteUlDemodTest();

	bool InitDefaulInputParam(LteUlInputParam *pInputParam);
	int DoDemodTest(LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);
	int GetIqDemodBufferSize();
	int GetIqDemodBuffer(double *pBuffer, int nBufferSize);
	int FreqDomainCal(LteUlInputParam* pInputParam, LteUlOutputParam *pOutputParam);
	void CleanUp();
	
	template<class Type>
	bool GetIqData(LteUlInputParam *pInputParam, Type tData);
	
	template<class Type>
	bool GetIqDataFormXFile(LteUlInputParam *pInputParam, Type tData,int fileType);

	bool SymbolTiming_FreqErrorEstimation(LteUlInputParam *pInputParam);
	bool FrameSync();
	bool GetIQFrame();

	template<class Type>
	bool DoSwFilter(Type * pIQRawData, int captureLength, int bandwidth, vector<complex_t> &iqComplex);

	//==============for LTE FreqDomainAnalysis//=============
	float TotalPower_dBm;
	vector<float> Spectrum_dBm;
	vector<float> Spectrum_W;
	vector<float> FreqList;
	float FracFreqError,InterFreerror,TotalFreqError;
 
	int DMRSSymbolStart;
	int FrameStart;
	int DutIndex;
private:
	LteUlDemodLog m_LogHandler;

	LteUlDemondSync m_SyncHandler;
	LteUlFreqErrorHandler m_FreErrorHandler;
	LteUlDemodEvmHandler m_EvmHandler;

	bool Init(LteUlInputParam *pInputParam);
	bool GetInputIqData(LteUlInputParam *pInputParam);
	bool DoDemodulation(LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);
	bool SetReSampleFacotr(LteUlInputParam *pInputParam);
	bool SwFilterEnable(int bandwidth, float sampleRate);
	int GetSwFilterBwType(int bandwidth);
	bool CellInputParamInitDefault(LteUlInputParam* pInputParam);

	CellParameter m_CellParam;
	DMRS* m_pUserDMRS;
	LteUlDemodParams m_UlParams;
	int m_ReSampleFactor;
	vector<complex_t> IQcomp;
	vector<complex_t> IQFrame;
	int m_CORpeakIndex;
	int m_SyncStartinFrame;

	float m_FreqErr;

	char m_msgFormat[FILE_NAME_LENGTH];
};

 template<class Type>
 bool LteUlDemodTest::GetIqData(LteUlInputParam *pInputParam, Type tData)
 {
	 bool bReturn = true;
	 int captureLength = m_UlParams.CaptureLen;
	 Type * pIQRawData = new Type[2 * captureLength];
	 int bandwidth = pInputParam->UserBW;
	 float sampleRate = pInputParam->SampleRate;
	 string iqDataFilePath(pInputParam->IqDataPath);

	 if (ReadIQDatafromFile(iqDataFilePath, 2 * captureLength, pIQRawData, tData))
	 {
		 int iqCompDatalength = captureLength / m_ReSampleFactor;

		 IQcomp.resize(iqCompDatalength);

		 if (SwFilterEnable(bandwidth, sampleRate))
		 {
			 DoSwFilter(pIQRawData, captureLength, bandwidth, IQcomp);
		 }
		 else
		 {
			 for (int k = 0; k < iqCompDatalength; k++)
			 {
				 IQcomp[k] = (complex_t(pIQRawData[2 * k * m_ReSampleFactor], pIQRawData[2 * k * m_ReSampleFactor + 1]));
			 }
		 }

		 LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("5. Read IQ data finished (ms) : "));
	 }
	 else
	 {
		 gLteStatusCode = LTE_UL_READ_IQ_FILE_FAILED;
		 bReturn = false;
	 }

	 delete[] pIQRawData;

	 return bReturn;
 }

 template<class Type>
 bool LteUlDemodTest::GetIqDataFormXFile(LteUlInputParam *pInputParam, Type tData, int fileType)
 {
	 bool bReturn = true;
	 int captureLength = m_UlParams.CaptureLen;
	 Type * pIQRawData = new Type[2 * captureLength];
	 string iqDataFilePath(pInputParam->IqDataPath);

	 int headerLineNum = GetFileHeaderLineNumber(fileType);

	 bReturn = ReadIQDatafromLineFile(iqDataFilePath, captureLength, pIQRawData, tData, headerLineNum);

	 if (bReturn)
	 {
		 int iqCompDatalength = captureLength / m_ReSampleFactor;

		 IQcomp.resize(iqCompDatalength);

		 for (int k = 0; k < iqCompDatalength; k++)
		 {
			 IQcomp[k] = (complex_t(pIQRawData[2 * k * m_ReSampleFactor], pIQRawData[2 * k * m_ReSampleFactor + 1]));
		 }

		 LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("5. Read IQ data in GetIqDataFormXFile finished (ms) : "));
	 }
	 else
	 {
		 bReturn = false;
	 }

	 delete[] pIQRawData;

	 return bReturn;
 }

 template<class Type>
 bool LteUlDemodTest::DoSwFilter(Type * pIQRawData, int captureLength, int bandwidth, vector<complex_t> &iqComplex)
 {
	 bool bReturn = false;
	 vector<complex_t> iqRaw;
	 int iqCompDatalength = captureLength / m_ReSampleFactor;

	 iqRaw.resize(captureLength);

	 for (int k = 0; k < captureLength; k++)
	 {
		 iqRaw[k] = (complex_t(pIQRawData[2 * k], pIQRawData[2 * k + 1]));
	 }

	 int bwType = GetSwFilterBwType(bandwidth);

	 myfilter(iqRaw, bwType);

	 for (int k = 0; k < iqCompDatalength; k++)
	 {
		 iqComplex[k] = iqRaw[k*m_ReSampleFactor];
	 }

	 return bReturn;
 }

#endif //headfile end