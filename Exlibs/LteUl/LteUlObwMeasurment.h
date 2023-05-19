#ifndef LteUlObwMeasurment_H
#define LteUlObwMeasurment_H


#include	"LteUlInputParam.h"
#include	"ComParaAndFun.h"

class LteUlObwMeasure
{
public:
	int DutIndex;
	LteUlObwMeasure();
	int InitDefault(LteUlObwInParam *pInParam);
	int GetCaptureLength(LteUlObwInParam *pInputParam);

	template<class Type>
	bool GetIqData(string iqDataFilePath, int captureLength, Type tData);

	void DoObwTest(LteUlObwInParam inParam, LteUlObwOutParam &OutParam);

	float RBStartCal(int n, int RBmax, int Numerlogy);

	bool LogInput(LteUlObwInParam inputParam);
	bool LogOutput(LteUlObwOutParam outParam);
	int GetFreqDomainAnalysisResult(float *pBuffer, int buffersize);

	//void WriteFreqPowerToFile(float *pbuffer, int nbufferLength, LteUlObwOutParam &OutParam);
	int GetFreqPowerBufferLength();
	bool SetReSampleFacotr(LteUlObwInParam *pInputParam);

	vector<complex_t> m_IQcomp;
private:
	int Initialize(LteUlObwInParam inParam, LteUlObwOutParam &OutParam);
	int CalculateIbeIndex(LteUlObwInParam inParam);
	int CalculateFrequencyRang(LteUlObwInParam inParam);
	int CalculateIqPower(LteUlObwInParam inParam, LteUlObwOutParam &OutParam);
	
	void WriteFreqPowerDataToBinFile(LteUlObwOutParam &outParam);
	int FDIQPointNumCal(LteUlObwInParam *pInputParam);

	float GetObwCalcualteResult();
	void  WriteFreqPowerToFile(float *pbuffer, int nbufferLength, LteUlObwOutParam &outParam);
	int m_SampleNumForPowerCalTotal;
	int m_SampleNumForPowerCal = 4096*4;
	float m_Freq_Step;
	float m_fs;
	float m_SCS;
	float m_RbFreqRange;
	float m_TotalRbFreqRange;

	int m_RBmax;
	LteUlObwInParam m_ObwInputParam;
	WavePara m_WaveParameterFD;

	vector<int> m_RBUsed;
	vector<int> m_RBType;
	vector<float> m_IBELimitMarginStandard;
	vector<complex_t> m_IQFD;//frequency domain complex data after FFT transform
	vector<float> m_IQFD_power;//Frequency domain power, unit W

	

	vector<float> m_IQOffsetRange;
	vector<float> m_SignalRange;
	vector<float> m_MirrorRange;
	vector<int> m_MirrorRB;
	float m_IBEGeneralTemp[3];
	vector<int> m_CarrierLeakRB;
	float m_IBERefdBm;

	float m_CarrierLeakageLimitMargin;
	float m_ImageLimitMargin;
	int m_captureLength;
	int m_ExtractorFreqPowerNum;

	vector<float> m_IBEMarginTestResultList;

	vector<float> m_Fre_index;
	vector<float> m_IBE;
	vector<float> m_IBELimitABS;
	vector<float> m_IQFD_powerdBm;
	vector<float> m_IQFDSpectrum_powerdBm;

	int m_FreqDomainMeasureType;
	int m_ReSampleFactor;
	int m_iqCompDataLength;

	char m_msgFormat[FILE_NAME_LENGTH];
};

template<class Type>
bool LteUlObwMeasure::GetIqData(string iqDataFilePath, int captureLength, Type tData)
{
	bool bReturn = true;
	Type * pIQRawData = new Type[2 * captureLength];

	if (ReadIQDatafromFile(iqDataFilePath, 2 * captureLength, pIQRawData, tData))
	{
		int iqCompDataLength = captureLength / m_ReSampleFactor;

		m_IQcomp.resize(iqCompDataLength);

		for (int k = 0; k <iqCompDataLength; k++)
		{
			m_IQcomp[k] = (complex_t(pIQRawData[2 * k * m_ReSampleFactor], pIQRawData[2 * k * m_ReSampleFactor + 1]));
		}

		LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("LteUlObwMeasure  GetIqData finished! "));
	}
	else
	{
		bReturn = false;
	}

	delete[] pIQRawData;

	return bReturn;
}









#endif
