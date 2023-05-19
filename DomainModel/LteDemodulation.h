#ifndef LTEDEMODULATION_H
#define LTEDEMODULATION_H

#include "BaseTask.h"

using namespace RM;

namespace RM {

class LteDemodulation {
 public:
  LteDemodulation();
  ~LteDemodulation();
  string run(string params);
  string getParams();
};
}  // namespace RM
#endif
