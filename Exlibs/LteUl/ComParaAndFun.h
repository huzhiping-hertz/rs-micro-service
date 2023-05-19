#ifndef ComParaAndFun_H
#define ComParaAndFun_H

#include	<iostream>
#include	<numeric>
#include	<complex>
#include	<cmath>
#include	<vector>
#include	<algorithm>
#include	<fstream>
#include	"SystemUtility.h"



#define		eps 1e-6 
#define		PI 3.14159265358979323846

#define SAMPLE_RATE_122_88	122.88
#define SAMPLE_RATE_61_44	61.44
#define SAMPLE_RATE_30_72	30.72
#define SAMPLE_RATE_15_36	15.36

typedef std::complex<double> complex_t;
using namespace std;

typedef struct WavePara {
	int FFTSize;
	int maxSCnumber;
	int maxRBNumber;
	float SR;
	int CP1;
	int CP2;
	float BW_Hz;
}WavePara;





extern bool WaveParamCal(WavePara& waveParam, int wBW);
extern complex_t W(int k, int n, int N);
extern complex_t format(complex_t& c);
extern double format(double& c);
extern int bitlen(int N);
extern int reverse_bit(int n, int len);
extern void resort(vector<complex_t>& x_n, int N);
extern vector<complex_t> VectorDevideScale(vector<complex_t> in, complex_t Gain);
extern float MaxMod(vector<complex_t> in);

extern vector<complex_t> IFFT(vector<complex_t> x_n);
extern vector<complex_t> FFT(vector<complex_t> x_n);
extern vector<complex_t> ifftshift(vector<complex_t> in);
extern vector<int> randomSequenceGenetator(int sequenceLength, int initC);
extern vector<complex_t> LTE_BaseSeqGeneration(int u, int v, int nULRB);
extern vector<complex_t> fftshift(vector<complex_t> in);
extern void AverageSpectralCal(vector<complex_t> IQ, int SegLen, vector<float>& Spectrout_W, vector<float>& Spectrout_dBm);
extern void AverageSpectralCalWithWin(vector<complex_t> IQ, int SegLen, vector<float>& Spectrout_W, vector<float>& Spectrout_dBm, vector<float> win);
extern void SpectruCal(vector<float>& in, float SR, int side);
extern void SpectruCal_W(vector<float>& in, float SR, int side);
extern void MoveSmooth(vector<float>& in, int Len);
extern void SpectrumDCSmooth(vector<float>& in);
extern vector<complex_t> MaxNormalization(vector<complex_t> in);
extern complex_t ConjCal(complex_t in);
extern float Mod(complex_t t);
extern vector<complex_t> Normalization(vector<complex_t> in);
extern void ComplexVectorMod(vector<complex_t> in, vector<float>& out);
extern void P_Mag_Cal(vector<complex_t> IQ, int FFTsize, int DetectRange, vector<float>& Pdetect, vector<float>& Magdetect);
extern void SpikeRemove(vector<float> in, int HL, float thre, vector<float>& out);
extern vector<float> SlidingCOR(vector<complex_t> IQin, int CORRange, int Period, int L);
extern vector<float> SlidingCORDS(vector<complex_t> IQin, int CORRange, int Period, int L, int CPPeriod);
extern vector<float> SlidingCORDSinRange(vector<complex_t> IQin, vector<int> CORRange, int Period, int L, int CPPeriod);
extern vector<float> SlidingCORNoNormalizationMidCP(vector<complex_t> IQin, int CORRange, int Period, int L);
extern void MyHistogram(vector<float> in, int SegNum, vector<float>& x, vector<int>& y);
extern vector<float> synccorinRange(vector<complex_t> IQ, vector<complex_t> SS, int SyncPostion, vector<int> Range, int repeat, int nCPPeriod, int SyncOffsettoS1);
extern vector<float> synccorinRange2(vector<complex_t> IQ, vector<complex_t> SS, int SyncPostion, int Center, int extend, int repeat, int nCPPeriod, int SyncOffsettoS1);
extern void synccorinRange2_returnIndex(vector<complex_t> IQ, vector<complex_t> SS, int SyncPostion, int Center, int extend, int repeat, int nCPPeriod, int SyncOffsettoS1, int& corPeakIndex);
extern void MoveJudge(vector<float> Mag, vector<float> Phase, int CP1, int CP2, int FFTsize, int SamplePerCPPeriod, vector<int>& Index, float& PhaseDetect);
extern float PhaseConstDetect(vector<float> in, int HalfLen);
extern vector<float> synccorinRangeWithDoubleDMRS(vector<complex_t> IQ, vector<complex_t> SS1, vector<complex_t> SS2, int SyncPostion, vector<int> Range, int DMRSPeriod);
extern vector<float> synccor(vector<complex_t> IQ, vector<complex_t> SS);
extern vector<int> SymbolTiming(vector<complex_t> IQSample, int CP1, int CP2, int FFTSize, float SR, float& PhaseDetectResult);
extern vector<float> synccorinRangeLTE(vector<complex_t> IQ, vector<complex_t> SS, int SyncPostion, vector<int> Range);// SStart表示同步序列在frame中的起始位置
// SStart is the start position of Sync sequence
extern void synccor_DFT_returnIndex(vector<complex_t> IQ, vector<complex_t> SS, int SyncPostion, int& corPeakIndex, int nSamplePerSlot);

extern float CFOEstimation(vector<complex_t> IQ, int start, int L, int N, float SR);
extern float CFOEstimationbyMidCP(vector<complex_t> IQ, int start, int L, int N, float SR);

extern void VectorElementGet(vector<complex_t> in, vector<int> ElementIndex, vector<complex_t>& out);
//extern int SymStartCal(int CP1, int CP2, int fftsize, int N);
extern int SymStartCal(WavePara waveParam, int N);
extern float QPSKEVMCcal(complex_t in);
extern complex_t QPSKDeci(complex_t in);
extern complex_t QAMDec(complex_t in, int ModOrder, float PowerBoostdB);
extern float Myregress(vector<float> x, vector<float> y, int N);
extern float QAMEVMCal(complex_t in, int ModOrder, float PowerBoostdB);
extern vector<int> FindAbove(vector<float> in, float level, int center);
extern float average(vector<float> x);
extern bool Freqoffset(vector<complex_t> &IQin, float Fsample, float freqerror);
extern void Complex_VectorElementGetbyIndex(vector<complex_t> in, int S1, int S2, vector<complex_t>& out);
extern void Float_VectorElementGetbyIndex(vector<float> in, int S1, int S2, vector<float>& out);
extern void Complex_VectorCombine(vector<complex_t> in1, vector<complex_t> in2, vector<complex_t>& out);
extern float MySign(float in);
extern long GetIqFileSampleNumber(char* iqFilePath, int rwUnitSize);
extern bool WriteToBinFile(string fileFullPath, float *pbuffer, long nFileTotalSize);
extern float PowerCalinRange(float Freq_Start, float Freq_Step, vector<float> dataFreq, float f1, float f2);
extern float PowerCalinRange_W(float Freq_Start, float Freq_Step, vector<float> dataFreq, float f1, float f2);
extern float FindMax(float a, float b);
extern int Next2Power(int in);
extern void Magfilter(vector<float> in, int HL, vector<float>& out);

//extern float BW_index2BW_Hz[15];
extern int GetDataFileRwUnitSize(char* fileFullPathName);
//extern void AverageSpectralCal(vector<complex_t> IQ, int SegLen, vector<float>& Spectrout_W, vector<float>& Spectrout_dBm);
//BWtype=1,20M;BW=2:40M;
extern void myfilter(vector<complex_t> &in, int BWtype);
void MyHist(vector<float> in, int Num, vector<float>& a, vector<int>& b);

extern bool IsSampleReateEqual(float sampleRate, float expectSampleRate);
extern int GetFileHeaderLineNumber(int fileType);

template<class Type>
bool ReadIQDatafromFile(string filePath, int len, Type *pIqData, Type data)
{
	bool bReturn = true;
	ifstream ifile;     //ifile Input file stream object 

	ifile.open(filePath, ios::binary);

	if (ifile.is_open())
	{
		ifile.read((char*)pIqData, len * sizeof(Type));

		ifile.close();
	}
	else
	{
		string msg;

		msg = "ReadIQDatafromFile is not open.The file path = " + filePath;

		Log(LOG_LEVEL_ERROR, const_cast<char*>(msg.c_str()));

		bReturn = false;
	}

	return bReturn;
}


//AWF is use by HY VST board , format is  that. Header 6 lines , then followed by IQ
/*
Technologies,
WaveformName,C:\waveform\NR
NoOfPoints,2580480
SampleRate,122880000
Bandwidth,
MarkerFile,
-0.009156,0.010743,0,0,0,0
-0.012909,0.009491,0,0,0,0
*/
//CSV TXT line data format I,Q such as 2.58257714740179E-06,1.87842293699909E-06

template<class Type>
bool ReadIQDatafromLineFile(string filePath, int len, Type* pIqData, Type data, int headerLineNumber)
{
	bool bReturn = true;
	ifstream ifile;     //ifile Input file stream object 
	Type I, Q;
	int j = 0;
	char msgFormat[FILE_NAME_LENGTH * 2];
	string typeName = typeid(I).name();

	ifile.open(filePath, ios::in);

	if (ifile.is_open())
	{
		string line;
		string field;

		for (int i = 0; i < len; i++)
		{
			getline(ifile, line); //getline(inFile, line) read datt from csv file by line 
			if (i < headerLineNumber) // ignore the header
			{
				continue;
			}
			else
			{
				istringstream sin(line); //Put string line data to string stream sin 

				getline(sin, field, ','); //Get charactor from sin to filed string , split by "," 
				I = atof(field.c_str());

				getline(sin, field, ','); //Get charactor from sin to filed string , split by "," 
				Q = atof(field.c_str());

				pIqData[j++] = I;
				pIqData[j++] = Q;

				if (typeName == "float" || typeName == "double")
				{
					sprintf(msgFormat, "I, Q ,%16.10f,%16.10f,", I, Q);
				}
				else if (typeName == "int" || typeName == "short")
				{
					sprintf(msgFormat, "I, Q ,%d, %d,", I, Q);
				}

				LogByDutIndex(0, LOG_LEVEL_RD, msgFormat);
			}		
		}

		ifile.close();
	}
	else
	{
		string msg;
		msg = "ReadIQDatafromLineFile is not open.The file path = " + filePath;

		Log(LOG_LEVEL_ERROR, const_cast<char*>(msg.c_str()));

		bReturn = false;
	}

	return bReturn;
}

template<class Type>
bool WriteDataToBinFile(string fileFullPath, Type *pbuffer, int nFileTotalSize)
{
	bool bReturn = false;
	ofstream fileOut;
	string msg;
	int DutIndex = 0;

	fileOut.open(fileFullPath, std::ios::out | std::ios::binary);

	if (fileOut.is_open())
	{
		fileOut.write((char *)pbuffer, nFileTotalSize);

		fileOut.close();

		bReturn = true;

		msg = "WriteToBinFile file path = " + fileFullPath;

		LogByDutIndex(DutIndex, LOG_LEVEL_INFOR, const_cast<char*>(msg.c_str()));

		int unitSize = sizeof(Type);
		string typeName = typeid(Type).name();

		msg = "WriteToBinFile file size = " + to_string(nFileTotalSize) + " RwUnitSize= " + to_string(unitSize) + " ,Type Name = " + typeName;

		LogByDutIndex(DutIndex, LOG_LEVEL_INFOR, const_cast<char*>(msg.c_str()));

	}
	else
	{
		msg = "WWriteToBinFile open file failed  " + fileFullPath;

		LogByDutIndex(DutIndex, LOG_LEVEL_ERROR, const_cast<char*>(msg.c_str()));
	}

	return bReturn;
}
#endif// header file ComParaAndFun_H end

