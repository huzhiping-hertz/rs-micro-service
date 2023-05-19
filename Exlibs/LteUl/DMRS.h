
#ifndef DMRS_H
#define DMRS_H

#include	<string>
#include	<complex>
#include	<vector>
#include	<iostream>
#include	<math.h>
#include	"CellParameter.h"
#include	"LteUlDemodParams.h"
#include	"ComParaAndFun.h"
#include	"myfft.h"
#include	"SystemUtility.h"
#include	"ComParaAndFun.h"

typedef std::complex<double> complex_t;
using namespace std;


class DMRS
{
public:
	DMRS();

	int DMRSSymbolinSlot;//��0��ʼ
	vector<int> DMRSSymbolIndex;//��0��ʼ	
	vector<vector<complex_t> > DMRSarray;//

	void CaculateSequence(CellParameter &CellParam, LteUlDemodParams &ulParams);

	void Init(CellParameter &CellParam, int cnusedSubcin,int SlotNumPerFrame);

	void TimeDomainCaculate(CellParameter &CellParam, LteUlDemodParams &ulParams);
	vector<complex_t>  LTE_DMRSseqGeneration(int N_Cell_ID, int Delta_ss, int n_1_DMRS, int n_2_DMRS, int n_s, int nULRB, SeqHopEnabled seq_hop, GroupHopEnabled group_hop);
	
	bool IsDmrsConfigType1();

	bool IsDmrsConfigType2();

	//bool IsCpSignal();

private:
	vector<complex_t> m_DMRSSeq;

	vector<complex_t> m_DmrstoSync;

	void setDMRS(CellParameter &CellParam, int cnusedSubcin);

	void PatternIni(int SlotPerFrame);

	void DmrsArrayInit(int SlotNumPerFrame,int nCarrierUsed);

	void CaculateDmrsSeq(CellParameter &CellParam);

	//void InitCarrierIndexInFFT(CellParameter &CellParam, LteUlDemodParams &ulParams);

	//void CalcuateSymbolStartPosition(LteUlDemodParams &ulParams);
	
	void CacluateSyncArray(int layerNumber, LteUlDemodParams &ulParams);

	//void CacluateSyncTimeDomainArray(LteUlDemodParams &ulParams);
};



#endif