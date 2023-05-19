#ifndef LteUlDemodSync_H
#define LteUlDemodSync_H


#include	"SystemUtility.h"
#include	"DMRS.h"
#include	"LteUlDemodParams.h"

class LteUlDemondSync
{
public:
	LteUlDemondSync();
	bool Sync(DMRS* pUserDMRS, LteUlDemodParams &ulParams, CellParameter &cellParam,vector<complex_t> &iqComp, int &corPeakIndex, int &syncStartinFrame);
	int DutIndex;

private:
	bool CpSync(LteUlDemodParams &ulParams, vector<complex_t> &iqComp);
	bool CalculateCorrelation(DMRS* userDMRS, LteUlDemodParams &ulParams, CellParameter &cellParam, vector<complex_t> &iqComp);
	//center is max index in Cp Sync 
	bool SyncByDMRSinFD(int center, int offset, DMRS* pUserDMRS, LteUlDemodParams &ulParams, CellParameter &cellParam, vector<complex_t> &iqComp, int & Peak);
	
	int m_CORpeakIndex;
	int m_SyncStartinFrame;
	char m_msgFormat[FILE_NAME_LENGTH];
	vector<float> SlideCorResult;
};

#endif
