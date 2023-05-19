#ifndef __myfft_h
#define __myfft_h 

#pragma once
#include	<complex>
#include	<vector>
#include	<cmath>
#include	"data.h"
#include	"ComParaAndFun.h"

typedef std::complex<double> complex_t;
using namespace std;

extern float mysin(float x);
extern float mycos(float x);
extern float myfabs(float x);
extern float mysqrt(float x);
extern int mypow(int i,int j);
extern int mylog(size_t n,int a);

extern void dft(const float x[],float real[],float imag[],const int n,int isign);
extern int rev(int i,int m);
extern void fft(const float real_in[],const float imag_in[],float real_out[],float imag_out[],const int n,int isign);

extern vector<complex_t> vectorfft(vector<complex_t> xin, int isign);

extern vector<complex_t> vectorfftanypoint(vector<complex_t> xin, int isign);


#endif//end header file

