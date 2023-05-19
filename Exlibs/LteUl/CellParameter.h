#ifndef CellParameter_H
#define CellParameter_H

#include <string>
#include "LteUlInputParam.h"

using std::string;
class CellParameter
{
public:
	//Signal Sample params
	float SampleRate;
	float SampleTime;
	int RwUnitSize;

	int CellID;
	int Bandwidth; // 
	LteDuplexMode Duplex;
	LteDirectionType Direction;
	LTECpType CPType;
	int RBOffset;
	int RBNumber;
	LteModulationMode Modulation;//Auto,

	//  DMRS Parameter;
	int Delta_ss = 0;
	int n_1_DMRS = 0;
	int n_2_DMRS = 0;
	SeqHopEnabled seq_hop_enabled;
	GroupHopEnabled group_hop_enabled;
	float DMRSBoostdB;
	

	CellParameter();

	void SetCellParameter(LteUlInputParam *pInputParam);

	void SetSystemParameter(LteUlInputParam *pInputParam);

	void SetDMRSParameter(LteUlInputParam *pInputParam);
};

#endif