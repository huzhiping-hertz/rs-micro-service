#ifndef LteUlDemodParams_H
#define LteUlDemodParams_H


#include	<string>
#include	<math.h>
#include	"ComParaAndFun.h"
#include	"CellParameter.h"
#include	"SystemUtility.h"


using std::string;

extern double FrameDuration;
extern int DCExclude;//�����ڲ�����DC���ز�ʱȥ��һ���ز�����ʼ����ʱ��Ϊ0.
extern int DMRSSymbolToSync;//����frame�еڼ���DMRS���Ž������ͬ������Ŵ�0��ʼ
extern int nSCperRB;
extern int CPSyncRangeExtend;//CP�߽�����Range
extern int nSlottoDemod;

class LteUlDemodParams
{
public:
	int DutIndex;
	int SymbolPerCPPeriod;// 7; 
	int SymbolPerSlot;// = 7; 
	int SlotPerFrame;//; = 20;
	int SCperRB;//= 12; 
	float Slot_duration;// = 0.5e-3;
	float CPPeriod_duration;// = 0.5e-3; 
	//DMRSSymbolinSlot = 4; 
	float Frame_duration;// = 10e-3;

	int FrameStartDetect;
	int SymbolPerFrame;
	int nCarrierUsed;
	int CarrierStartinOFDM;
	int CarrierStopinOFDM;
	int CarrierStartinFFT;
	int CarrierStopinFFT;
	int SampleNumPerCPPeriod;
	int SampleNumPerSlot;
	int SampleNumPerFrame;
	vector<int>Symbol_Start_perFrame;
	int CaptureLen;
	int SlotForSync;
	int DMRSSymbolForSync;
	int SyncPostioninFrame;
	WavePara WaveParam;
	bool Retest;
	LteUlDemodParams();

	~LteUlDemodParams();

	void InitParams(LteUlInputParam *pInputParam, CellParameter &cellParam);
};





#endif //headfile end