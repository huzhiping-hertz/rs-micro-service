#ifndef LteUlDemodFreqErrorHandler_H
#define LteUlDemodFreqErrorHandler_H


#include	"SystemUtility.h"
#include	"LteUtility.h"
#include	"DMRS.h"
#include	"LteUlDemodParams.h"

class LteUlFreqErrorHandler
{
public:
	LteUlFreqErrorHandler();
	bool CalFreqErrorAndCompensation(DMRS* userDMRS, LteUlDemodParams& ulParams, vector<complex_t> &IQcomp, vector<complex_t> &IQFrame, int corPeakIndex, int syncStartinFrame, float &freError);
	int DutIndex;
private:
	bool CalFreqError(DMRS* userDMRS, LteUlDemodParams& nrUlParams, vector<complex_t> &IQcomp, vector<complex_t> &IQFrame);
	bool InitIqFrame(int SamplePerFrame, vector<complex_t> &IQcomp, vector<complex_t> &IQFrame, int FrameStart);

	int m_CORpeakIndex;
	
	int m_SyncStartinFrame;
	float m_FreqErr;

	char m_msgFormat[FILE_NAME_LENGTH];
	vector<float> SlideCorResult;
};

#endif
