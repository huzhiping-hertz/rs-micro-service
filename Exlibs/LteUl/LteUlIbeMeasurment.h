#ifndef LteUlIbeMeasurment_H
#define LteUlIbeMeasurment_H


#include	"LteUlInputParam.h"
#include	"ComParaAndFun.h"

class LteUlIbeMeasure
{
public:
	int DutIndex;
	LteUlIbeMeasure();
	int InitDefault(LteUlIbeInParam *pIbeInParam);
	int GetCaptureLength(LteUlIbeInParam *pInputParam);

	template<class Type>
	bool GetIqData(string iqDataFilePath, int captureLength, Type tData);

	template<class Type>
	bool GetIqDataFormXFile(string iqDataFilePath, int capturelength, Type tData, int fileType);

	void DoIbeTest(LteUlIbeInParam inParam, LteUlIbeOutParam &OutParam);

	float RBStartCal(int n, int RBmax, int Numerlogy);

	bool LogIbeInput(LteUlIbeInParam inputParam);
	bool LogIbeOutput(LteUlIbeOutParam outParam);
	int GetFreqDomainAnalysisResult(float *pBuffer, int buffersize);

	void WriteFreqPowerToFile(float *pbuffer, int nbufferLength, LteUlIbeOutParam &OutParam);
	int GetFreqPowerBufferLength();
	bool SetReSampleFacotr(LteUlIbeInParam *pInputParam);
	void SetIqComplex(vector<complex_t> iQComplexData);

	vector<complex_t> m_IQcomp;
private:
	int Initialize(LteUlIbeInParam inParam, LteUlIbeOutParam &OutParam);
	int CalculateIbeIndex(LteUlIbeInParam inParam);
	int CalculateFrequencyRang(LteUlIbeInParam inParam);
	int CalculateIqPower(LteUlIbeInParam inParam, LteUlIbeOutParam &OutParam);
	int CalculateIbe(LteUlIbeInParam inParam, LteUlIbeOutParam &OutParam);
	int CalculateIbeLimitMargin(LteUlIbeInParam inParam, LteUlIbeOutParam &OutParam);
	int SetIbeOutputResult(LteUlIbeOutParam &OutParam);
	void CalcuateAbsolutionFreq();
	void WriteFreqPowerDataToBinFile(LteUlIbeOutParam &outParam);
	int FDIQPointNumCal(LteUlIbeInParam *pInputParam);

	float GetObwCalcualteResult(LteUlIbeInParam inParam);

	int m_SampleNumForPowerCalTotal;
	int m_SampleNumForPowerCal = 4096;
	float m_Freq_Step;
	float m_fs;
	float m_SCS;
	float m_RbFreqRange;
	float m_TotalRbFreqRange;
	float ChannelPower_dBm;

	int m_RBmax;
	LteUlIbeInParam m_IbeInputParam;
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
bool LteUlIbeMeasure::GetIqData(string iqDataFilePath, int captureLength, Type tData)
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

		LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("LteUlIbeMeasure  GetIqData finished! "));
	}
	else
	{
		bReturn = false;
	}

	delete[] pIQRawData;

	return bReturn;
}



template<class Type>
bool LteUlIbeMeasure::GetIqDataFormXFile(string iqDataFilePath, int capturelength, Type tData, int fileType)
{
	bool bReturn = true;
	int startIndex = 0;
	int resizeCaptureLength = capturelength;
	int headerLineNum = GetFileHeaderLineNumber(fileType);

	Type* pIQRawData = new Type[2 * capturelength];

	bReturn = ReadIQDatafromLineFile(iqDataFilePath, capturelength, pIQRawData, tData, headerLineNum);

	if (bReturn)
	{
		m_IQcomp.resize(resizeCaptureLength);

		for (int k = 0; k < resizeCaptureLength; k++)
		{
			m_IQcomp[k] = (complex_t(pIQRawData[2 * k + startIndex], pIQRawData[2 * k + 1 + startIndex]));
		}

		LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("5. Read in GetIqDataFormXFile IQ data finished (ms) : "));
	}
	else
	{
		bReturn = false;
	}

	delete[] pIQRawData;

	return bReturn;
}





#endif
