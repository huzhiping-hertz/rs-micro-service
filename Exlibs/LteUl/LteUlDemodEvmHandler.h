#ifndef LteUlDemodEvmHandler_H
#define LteUlDemodEvmHandler_H


#include	"DMRS.h"
#include	"Interp.h"
#include	"LteUlDemodParams.h"
#include	"LteUlInputParam.h"


class LteUlDemodEvmHandler
{
public:
	LteUlDemodEvmHandler();

	bool DoEvmCalculate(DMRS* userDMRS, LteUlDemodParams& ulParams, CellParameter &cellParam, vector<complex_t> &IQFrame, LteUlEvmCalculateType evmCalType);
	
	bool GetOutputResult(DMRS* userDMRS, LteUlDemodParams &ulParams, LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);

	int GetIqDemodBufferSize();
	int GetIqDemodBuffer(DMRS* userDMRS, double *pBuffer, int nBufferSize);
	int DutIndex;
private:

	bool CalIQdataFD(DMRS* userDMRS, LteUlDemodParams& nrUlParams, vector<complex_t> &IQFrame);
	bool DoDmrsChannelEstimate(DMRS* userDMRS, LteUlDemodParams& ulParams, vector<complex_t> &IQFrame);
	bool DoDmrsDataChannelEstimate(DMRS* userDMRS, LteUlDemodParams &ulParams, CellParameter &cellParam);
	bool DoChannelCompensation(DMRS* userDMRS, LteUlDemodParams &nrUlParams);
	bool CalculateEvm(DMRS* userDMRS, LteUlDemodParams &ulParams, CellParameter &cellParam);

	//DmrsChannelEstimate
	//bool InitDataFdActive(LteUlDemodParams &nrUlParams);	
	bool CalculateHrs(DMRS* userDMRS, LteUlDemodParams &nrUlParams);
	//bool CalculateHrsTwoDc(DMRS* userDMRS, LteUlDemodParams &nrUlParams);

	//DoDmrsDataChannelEstimate
	bool InitDmrsIndexTwoDc(DMRS* userDMRS, LteUlDemodParams &ulParams);
	bool CalDataFdActiveHrsAndRef(DMRS* userDMRS, LteUlDemodParams &ulParams, CellParameter &cellParam);
	bool CalDataFDbyHrsdata(DMRS* userDMRS, LteUlDemodParams &nrUlParams);


	//CalculateEvm 
	bool DisplayEvmResult();
	void GetIqConstellationData(vector<vector<complex_t>> iqDemodData, LteUlDemodParams &ulParams);
	int WriteToBinFile(char* folderPath, LteUlOutputParam *pOutputParam);

	bool IsEvmCalTypeHigh();
	vector<vector<complex_t> > dataFDNoEq;
	vector<vector<complex_t>>  m_dataFDActive;

	vector<vector<complex_t>>  m_dataFDActivewHrs;
	vector<vector<complex_t>>  m_dataFDActiveRef;

	vector<complex_t> m_Hrs;
	//vector<complex_t> m_HrswoDC;
	vector<complex_t> Hrsdata;

	vector<vector<complex_t>> m_dataFDEqwHrsNor;
	vector<vector<complex_t>> m_dataFDEqwHrsNor_dataOnly;
	vector<vector<complex_t>>  m_dataFDActive_DFT_final;

	//vector<float> m_CarrierIndexused;
	//vector<float> m_CarrierIndexusedwoDC;
	//vector<float> m_DmrsCarrierindexwoDC;

	vector<float> EVMPerSC;
	vector<float> EVMvsSymbol;
	vector<float> EVMPeakvsSymbol;

	float m_EvmHigh;
	float m_EvmLow;

	float m_EvmPeakHigh;
	float m_EvmPeakLow;
	float m_PhaseErr;

	LteUlEvmCalculateType m_EvmCalType;
	int m_SymbolOffset;

	vector<complex_t> m_IqConstellationData;
	int m_IqConstellationDataLength;

	char m_OutputFileLogFolder[FILE_NAME_LENGTH];
	char m_OutputFileName[FILE_NAME_LENGTH];

	char m_msgFormat[FILE_NAME_LENGTH];
	vector<float> SlideCorResult;
};

#endif
