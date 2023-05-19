#ifndef		LteUlAclr_H
#define		LteUlAclr_H

#include	"LteUlInputParam.h"


class LteUlAclrMeas
{
public:
	LteUlAclrMeas();
	int InitDefault(LteUlAclrInParam *pInputParam);
	int GetCaptureLength(LteUlAclrInParam *pInputParam);
	template<class Type>
	bool AclrGetIqData(LteUlAclrInParam *pInputParam, int captureLength, Type tData);

	void DoAclrMeas(LteUlAclrInParam aclrInParams, LteUlAclrOutParam &aclrOutParam);
	bool LogInput(LteUlAclrInParam inParam);
	bool LogOutput(LteUlAclrOutParam outParam);
	bool SetReSampleFacotr(LteUlAclrInParam *pInputParam);
	void SetIqComplex(vector<complex_t> iQCompMainChannel);
	int DutIndex;
private:
	float GetFreqRange(int Numerlogy, int nMaxRbNumber);
	void  CalculateIqFdPower(vector<complex_t> IqComplex, vector<float> &IqFdPower);
	float GetSampleFreqStep(int nSampleLength, float sampleRate);
	void  GetFreqStepAndRange(int BW, int Numerlogy, int nSampleLength,float SR);
	void  GetAclrNegativeValue(float freqStart, float freqStep, float freqHalfRange, vector<complex_t> IQcompLow, LteUlAclrOutParam &aclrOutParam);
	void  GetAclrPositiveValue(float freqStart, float freqStep, float freqHalfRange, vector<complex_t> IQcompHigh, LteUlAclrOutParam &aclrOutParam);
	
	template<class Type>
	bool GetIqData(string iqDataFilePath, int captureLength, int channelType, LteUlAclrInParam *pInputParam, vector<complex_t> &iqComplex, Type tData);

	int FDIQPointNumCal(LteUlAclrInParam *pInputParam);
	bool SwFilterEnable(int channelType, int bandwidth, float sampleRate);
	int GetSwFilterBwType(int bandwidth);

	template<class Type>
	bool DoSwFilter(Type * pIQRawData, int captureLength,int bandwidth,vector<complex_t> &iqComplex);

	void WriteFreqPowerDataToBinFile(LteUlAclrOutParam &outParam);
	void WriteFreqPowerToFile(float *pbuffer, int nbufferLength, LteUlAclrOutParam &outParam);
	int GetFreqDomainAnalysisResult(float *pBuffer, int buffersize);
	int GetFreqPowerBufferLength();
	float m_freqStep;
	float m_freqRange;
	vector<float> m_FreqIndex;
	float m_CarrierPower;

	float m_fs;
	int m_SampleNumForPowerCal = 4096;

	int m_ReSampleFactor;

	vector<float> m_IqFd;
	vector<float> m_IqFd_dBm;

	vector<complex_t> m_IQCompMainChannel;
	vector<complex_t> m_IQCompNegChannel;
	vector<complex_t> m_IQCompPosChannel;
	LteUlAclrInParam m_AclrInputParam;
	vector<float> m_IQFDSpectrum_powerdBm;

	char m_msgFormat[FILE_NAME_LENGTH];
};


template<class Type>
bool LteUlAclrMeas::AclrGetIqData(LteUlAclrInParam *pInputParam, int captureLength, Type tData)
{
	bool bReturn = true;
	string iqDataMain(pInputParam->IqWaveFilePathMainChannel);

	bReturn &= GetIqData(iqDataMain, captureLength, LTE_CHANNEL_TYPE_MAIN, pInputParam,m_IQCompMainChannel, tData);


	return bReturn;
}

template<class Type>
bool LteUlAclrMeas::GetIqData(string iqDataFilePath, int captureLength,int channelType, LteUlAclrInParam *pInputParam,vector<complex_t> &iqComplex,Type tData)
{
	bool bReturn = true;
	Type * pIQRawData = new Type[2 * captureLength];
	int bandwidth = pInputParam->BW;
	float sampleRate = pInputParam->SampleRate;

	if (ReadIQDatafromFile(iqDataFilePath, 2 * captureLength, pIQRawData, tData))
	{	
		int iqCompDataLength = captureLength / m_ReSampleFactor;

		iqComplex.resize(iqCompDataLength);

		//Special version to use the software filter for band 20M/40M
		if(SwFilterEnable(channelType, bandwidth, sampleRate))
		{
			DoSwFilter(pIQRawData, captureLength, bandwidth,iqComplex);
		}
		else
		{
			for (int k = 0; k < iqCompDataLength; k++)
			{
				iqComplex[k] = (complex_t(pIQRawData[2 * k * m_ReSampleFactor], pIQRawData[2 * k * m_ReSampleFactor + 1]));
			}
		}

		LogByDutIndex(DutIndex, LOG_LEVEL_NORMAL, const_cast<char*>("LteUlAclrMeas  GetIqData finished! "));
	}
	else
	{
		bReturn = false;
	}

	delete[] pIQRawData;

	return bReturn;
}

template<class Type>
bool LteUlAclrMeas::DoSwFilter(Type * pIQRawData, int captureLength, int bandwidth,vector<complex_t> &iqComplex)
{
	bool bReturn = false;
	vector<complex_t> iqRaw;

	iqRaw.resize(captureLength);

	for (int k = 0; k < captureLength; k++)
	{
		iqRaw[k] = (complex_t(pIQRawData[2 * k], pIQRawData[2 * k + 1]));
	}

	int bwType = GetSwFilterBwType(bandwidth);

	myfilter(iqRaw, bwType);

	for (int k = 0; k < captureLength / m_ReSampleFactor; k++)
	{
		iqComplex[k] = iqRaw[k*m_ReSampleFactor];
	}

	return bReturn;
}

#endif
