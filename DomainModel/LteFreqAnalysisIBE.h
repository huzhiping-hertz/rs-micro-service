#ifndef LTEFREQANALYSISIBE_H
#define LTEFREQANALYSISIBE_H

#include "BaseTask.h"

using namespace RM;

namespace RM {

	class LteFreqAnalysisIBE
	{

	public:
		LteFreqAnalysisIBE();
		~LteFreqAnalysisIBE();
		string run(string params);
		string getParams();
	};
}
#endif 
