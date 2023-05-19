#ifndef LteUlInputParam_H
#define LteUlInputParam_H


#include	<string>
#include	"SystemUtility.h"


using std::string;



struct LteUlInputParam
{
	int DutIndex;
	//Signal Sample params
	float SampleRate; // MSample/s
	float SampleTime; //ms
	int   RwUnitSize;
	int   InputSource;
	int  RawDataEnable;

	//  CellInputParam CellParam;
	int UserCellID;
	int UserBW;
	LteDuplexMode UserDuplex;
	LTECpType UserCPType;
	int UserRBOffset;
	int UserRBNumber;
	LteModulationMode UserModulation;//Auto,

	//  DMRS Parameter;
	int UserDelta_ss;
	int Usern_1_DMRS;
	int Usern_2_DMRS;
	SeqHopEnabled Userseq_hop_enabled;
	GroupHopEnabled Usergroup_hop_enabled;
	float UserDMRSBoostdB;


	char* IqDataPath;
	char* BinFileLogFolder;
};


struct LteUlOutputParam
{
	float FreqErr;
	float PhaseErr;
	float EvmHigh;
	float EvmLow;
	float EvmPeakHigh;
	float EvmPeakLow;
	float EVMvsSymbol[14];

	char fileFullPath[FILE_NAME_LENGTH];
	char FreqPowerFilePath[FILE_NAME_LENGTH];
	uint32_t totalLength;// the total Byte number
	int	rwSizeUnit;

	float TotalPower;
	//vector<float> EVMPerSC;
	//vector<float> EVMvsSymbol;
};

//IBE 
struct LteUlIbeInParam
{
	char IqDataPath[FILE_NAME_LENGTH];
	char BinFileLogFolder[FILE_NAME_LENGTH];
	char OutputFileName[FILE_NAME_LENGTH];
	//Signal Sample params
	float SampleRate; // MSample/s
	float SampleTime; //ms
	int   RwUnitSize;
	int   InputSource;

	float CenertFreq;
	int extractFactor;
	int BW;
	int RBoffset;
	int RBNum;
	int Numerlogy;
	int GetRawData;

	int FreqDomainMeasureType;
	float ObwPowerPercentage;
};

struct LteUlIbeOutParam
{
	int iWorstIBEIndex;
	float dWorstIBEMagin;
	float dIQOffset;
	float dMeasuredPower;
	float dCarrierPower;
	float dObwResult;

	char OutputFileFullPath[FILE_NAME_LENGTH];
	int TotalFileSize;
	int RwUnitSize;
};


struct LteUlAclrInParam
{
	char IqWaveFilePathMainChannel[FILE_NAME_LENGTH];
	char BinFileLogFolder[FILE_NAME_LENGTH];
	//Signal Sample params
	double SampleRate; // MSample/s
	double SampleTime; //ms
	int   RwUnitSize;
	int   InputSource;

	int BW;
	int Numerlogy;
	int GetRawData;
};

struct LteUlAclrOutParam
{
	float CarrierPower;

	float Aclr_E_UTRA_2_Neg;
	float Aclr_E_UTRA_1_Neg;
	float Aclr_E_UTRA_1_Pos;
	float Aclr_E_UTRA_2_Pos;

	float Aclr_UTRA_2_Neg;
	float Aclr_UTRA_1_Neg;
	float Aclr_UTRA_1_Pos;
	float Aclr_UTRA_2_Pos;
	char OutputFileFullPath[FILE_NAME_LENGTH];
};


//SEM
struct LteUlSemInParam
{
	char IqWaveFilePathMainChannel[FILE_NAME_LENGTH];
	char IqWaveFilePathNegChannel[FILE_NAME_LENGTH];
	char IqWaveFilePathPosChannel[FILE_NAME_LENGTH];
	char OutputFolderPath[FILE_NAME_LENGTH];

	//Signal Sample params
	float SampleRate; // MSample/s
	float SampleTime; //ms
	int   RwUnitSize;
	int   InputSource;
	int	  OutputMode;

	float CenterFrequency;
	int BW;
	int Numerlogy;
	int GetRawData;
	int ResampleEnable;
};

struct LteUlSemOutParam
{
	float SpecMargin[LTE_UL_SEM_TOTAL_RANGE_NUM];
	float SpecMarginFreq[LTE_UL_SEM_TOTAL_RANGE_NUM];

	float SpecMargin4Neg;
	float SpecMargin3Neg;
	float SpecMargin2Neg;
	float SpecMargin1Neg;

	float SpecMargin1Pos;
	float SpecMargin2Pos;
	float SpecMargin3Pos;
	float SpecMargin4Pos;

	float SpecMargin4NegFreq;
	float SpecMargin3NegFreq;
	float SpecMargin2NegFreq;
	float SpecMargin1NegFreq;

	float SpecMargin1PosFreq;
	float SpecMargin2PosFreq;
	float SpecMargin3PosFreq;
	float SpecMargin4PosFreq;
	char OutputFileFullPath[FILE_NAME_LENGTH];
};

struct LteUlSemRangItem
{
	vector<float> FreqIndex;
	vector<float> PowerRange;
	vector<float> PowerRangeLimit;
};

struct LteUlChannelPowerInParam
{
	char IqWaveFilePathMainChannel[FILE_NAME_LENGTH];
	char BinFileLogFolder[FILE_NAME_LENGTH];
	//Signal Sample params
	float SampleRate; // MSample/s
	float SampleTime; //ms
	int   RwUnitSize;
	int   InputSource;

	int BW;
	int Numerlogy;
};

struct LteUlChannelPowerOutParam
{
	float CarrierPower;
};

struct LteUlObwInParam
{
	char IqDataPath[FILE_NAME_LENGTH];
	char BinFileLogFolder[FILE_NAME_LENGTH];
	char OutputFileName[FILE_NAME_LENGTH];
	//Signal Sample params
	float SampleRate; // MSample/s
	float SampleTime; //ms
	int   RwUnitSize;
	int   InputSource;

	float CenertFreq;
	int extractFactor;
	int BW;
	int RBoffset;
	int RBNum;
	int Numerlogy;
	int GetRawData;

	int FreqDomainMeasureType;
	float ObwPowerPercentage;
};

struct LteUlObwOutParam
{
	float dObwResult;
	char OutputFileFullPath[FILE_NAME_LENGTH];
};

#endif //headfile end