#ifndef LteUlDll_H
#define LteUlDll_H


#include	"LteUlInputParam.h"


extern "C"  int STDCALL DllLteUlInitDemodInputParamDefaul(int dutIndex,LteUlInputParam *pInputParam);
extern "C"  int STDCALL DllLteUlDemod(int dutIndex, LteUlInputParam *pInputParam, LteUlOutputParam *pOutputParam);
extern "C"  int STDCALL DllLteUlLibEnter(int dutIndex);
extern "C"  int STDCALL DllLteUlLibExit(int dutIndex);
extern "C"  int STDCALL DllGetLteUlDemodIqBufferSize(int dutIndex);
extern "C"  int STDCALL DllGetLteUlDemodIqBuffer(int dutIndex, double *pBuffer, int nBufferSize);

//FreqDomian Analyisis dll interface
extern "C" int STDCALL	DllLteUlIbeInitDefaut(int dutIndex, LteUlIbeInParam *pIbeInParams);
extern "C" int STDCALL  DllLteUlGetFdaBufferSize(int dutIndex);

extern "C"  int STDCALL DllLteUlIbeTest(int dutIndex, LteUlIbeInParam *pIbeInParams, LteUlIbeOutParam *pIbeOutParams);
extern "C"  int STDCALL DllLteUlGetFdaResult(int dutIndex, float *pBuffer, int buffersize);
extern "C"  int STDCALL DllLteUlAclrInitDefaul(int dutIndex, LteUlAclrInParam *pInputParam);
extern "C"  int STDCALL DllLteUlAclrTest(int dutIndex, LteUlAclrInParam *pAclrInParams, LteUlAclrOutParam *pAclrOutParams);
extern "C"  int STDCALL DllLteUlSemInitDefaulInputParam(int dutIndex, LteUlSemInParam *pInputParam);
extern "C"  int STDCALL DllLteUlSemTest(int dutIndex, LteUlSemInParam *pInParams, LteUlSemOutParam *pOutParams);
extern "C"  int STDCALL DllLteUlSemGetRangeLength(int dutIndex, int rangeId);
extern "C"  int STDCALL DllLteUlSemGetRangeArrayResult(int dutIndex, int rangId, float *freqArray, float *powerArray, float *powerLimitArray);

extern "C"  int STDCALL DllLteUlChannelPowerInitDefaut(int dutIndex, LteUlChannelPowerInParam *pInputParam);
extern "C"  int STDCALL DllLteUlChannelPowerTest(int dutIndex, LteUlChannelPowerInParam *pInParams, LteUlChannelPowerOutParam *pOutParams);
extern "C" int STDCALL	DllLteUlObwInitDefaut(int dutIndex, LteUlObwInParam *pInParams);
extern "C"  int STDCALL DllLteUlObwTest(int dutIndex, LteUlObwInParam *pInParams, LteUlObwOutParam *pOutParams);

#endif