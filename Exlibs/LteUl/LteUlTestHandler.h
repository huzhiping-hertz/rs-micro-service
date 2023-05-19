#ifndef LteUlTestHandler_H
#define LteUlTestHandler_H


#include	"LteUlSemHandler.h"
#include 	"LteUlIbeMeasurment.h"
#include	"LteUlAclr.h"
#include	"LteUlInputParam.h"
#include	"LteUlDemodTest.h"
#include	"LteUlChannelPower.h"
#include 	"LteUlObwMeasurment.h"

class LteUlTestHandler
{
public:
	int DutIndex;
	LteUlTestHandler();
	~LteUlTestHandler();
	void Init();
	void Init(int measureType);
	void InitByDutIndex(int dutIndex);

	int GetIqDemodBufferSize();
	int GetIqDemodBuffer(double *pBuffer, int nBufferSize);

	//LTE Ul
	bool LteUlDemodInitDefault(LteUlInputParam *pInputParam);
	int LteUlDemodulation(LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);

	int IbeInitDefault(LteUlIbeInParam *pIbeInParams);
	bool IbeGetIqData(LteUlIbeInParam *pInputParam);
	int IbeTest(LteUlIbeInParam *pIbeInParams, LteUlIbeOutParam *pIbeOutParams);
	int GetFreqDomainAnalysisBufferSize();
	int GetFreqDomainAnalysisResult(float *pBuffer, int buffersize);

	int AclrInitDefault(LteUlAclrInParam *pInputParam);
	bool NrUlAclrGetIqData(LteUlAclrInParam *pAclrInParam);
	int AclrTest(LteUlAclrInParam *pAclrInParams, LteUlAclrOutParam *pAclrOutParams);

	int SemInitDefaultInputParams(LteUlSemInParam *pInputParam);
	int SemTest(LteUlSemInParam *pInParams, LteUlSemOutParam *pOutParams);
	int SemGetRangeLength(int rangId);
	int SemGetRangeArrayResult(int rangId, float *freqArray, float *powerArray, float *powerLimitArray);

	int ChannelPowerInitDefault(LteUlChannelPowerInParam *pInputParam);
	bool ChannelPowerGetIqData(LteUlChannelPowerInParam *pInputParam);
	int ChannelPowerTest(LteUlChannelPowerInParam *pInParams, LteUlChannelPowerOutParam *pOutParams);
	int ObwTest(LteUlObwInParam *pInParams, LteUlObwOutParam *pOutParams);

	int ObwInitDefault(LteUlObwInParam *pInParam);

	int DoCleanUp();
	int DoCleanUp(int measureType);
private:
	LteUlDemodTest *m_pDemodHandler;

	LteUlAclrMeas *m_pAclrHandler;
	LteUlIbeMeasure *m_pIbeTestHandler;
	LteUlSemHandler *m_pSemTestHandler;
	LteUlChannelPowerMeas *m_pChannelPowerHandler;
	LteUlObwMeasure *m_pObwHandler;

	char m_msgFmt[FILE_NAME_LENGTH];

	bool DemodGetIqData(LteUlInputParam *pInputParam);
	bool ObwGetIqData(LteUlObwInParam *pInputParam);
	void CleanUp();
};







#endif
