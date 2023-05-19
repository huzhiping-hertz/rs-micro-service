#ifndef LteUlSemHandler_H
#define LteUlSemHandler_H


#include	"LteUlInputParam.h"




class LteUlSemHandler
{
public:
	int DutIndex;
	LteUlSemHandler();
	int InitDefaultInputParams(LteUlSemInParam *pInputParam);

	bool DoSemTest(LteUlSemInParam *pInParam, LteUlSemOutParam *pOutParams);

	int GetRangeLength(int rangId);

	bool GetRangeArrayResult(int rangId, float *freqArray, float *powerArray, float *powerLimitArray);
	bool SetReSampleFacotr(LteUlSemInParam *pInputParam);
	// 4 ~ 7 is PositiveRange 1 ~ 4, 0 ~ 3 for NegativeRange 4 ~ 1
	LteUlSemRangItem m_LteUlSemRangArray[LTE_UL_SEM_TOTAL_RANGE_NUM];
private:
	bool Initialize(LteUlSemInParam inParam);
	int  FDIQPointNumCal(LteUlSemInParam inParam);
	bool InitIqComplex(LteUlSemInParam inParam);
	bool SetIqComplexData(string filePath, int channelType, LteUlSemInParam inParam, vector<complex_t> &iqComplex);
	float SEM_TTdB(int BW_index, float fc);
	void SEMParamerCal(int BW_index, float* DeltafOOB_Start, float* DeltafOOB_Stop, float* MeasureBW, float* SEMLimit, float TT);
	void InitBwOffset(int BW_index);
	void InitSemParams(int BW_index, float fc);
	void InitLocalFreqIndex();
	int  CalculateRangeValue(int rangIndex, int marginIndex, LteUlSemRangItem &rangItem, float *SEMMargin);
	void UpdateSemOutParam(LteUlSemOutParam *pOutParams);
	bool LogInput(LteUlSemInParam *pInputParam);
	bool LogOutput(LteUlSemOutParam *pOutParams);

	bool LogAllRangeResult();
	bool LogRangeResult(int rangeId);
	void WriteFreqPowerToFile(int rangId, float *pbuffer, int nbufferLength, LteUlSemOutParam &outParam);
	bool SwFilterEnable(int channelType, int bandwidth, float sampleRate);
	int GetSwFilterBwType(int bandwidth);
	bool DoSwFilter(float * pIQRawData, int captureLength, int bandwidth, vector<complex_t> &iqComplex);

	void WriteFreqPowerDataToBinFile(LteUlSemOutParam &outParam);
	void WriteFreqPowerToFile(float *pbuffer, int nbufferLength, LteUlSemOutParam &outParam);
	int GetFreqPowerBufferLength();
	int GetFreqDomainAnalysisResult(float *pBuffer, int buffersize);
	bool CalculateSemValue(LteUlSemInParam *pInParam, LteUlSemOutParam *pOutParams);
	
	int m_SampleNumForPowerCal=4096;
	int m_SampleNumForPowerCalTotal;
	vector<complex_t> m_IQcomp;//input main channel IQ data
	//vector<complex_t> m_IQcompLow;//input negative channel IQ data
	//vector<complex_t> m_IQcompHigh;//input positive channel IQ data
	
	float m_fs;
	float m_Freq_Step;
	float m_BwOffset;
	float m_BW_Hz;
	vector<float> m_Fre_index_SEM_local;
	vector<float> m_IqFd;
	//vector<float> m_IqFdPos;

	vector<float> m_IqFd_dBm;
	//vector<float> m_IqFdPos_dBm;
	vector<float> m_IQFDSpectrum_powerdBm;
	float m_TT;
	float m_DeltafOOB_Start[LTE_UL_SEM_HALF_RANGE_NUM] = { 0 };
	float m_DeltafOOB_Stop[LTE_UL_SEM_HALF_RANGE_NUM] = { 0 };
	float m_MeasureBW[LTE_UL_SEM_HALF_RANGE_NUM] = { 0 };
	float m_SEMLimit[LTE_UL_SEM_HALF_RANGE_NUM] = { 0 };

	float m_LteUlSemMaxMarginFreq[LTE_UL_SEM_TOTAL_RANGE_NUM];

	int m_ReSampleFactor;
	int m_IqCompDataLength;
	LteUlSemInParam m_SemInputParam;
	LteUlSemOutParam m_SemOutputParam;
	

	char m_msgFormat[FILE_NAME_LENGTH];
};













#endif