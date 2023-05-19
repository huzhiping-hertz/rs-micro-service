#ifndef Interp_H
#define Interp_H

#pragma once
#include <iostream> 
#include <vector> 
#include <limits> 
#include <cmath> 
#include <complex>

typedef std::complex<double> complex_t;
template<typename Real>

extern size_t nearestNeighbourIndex(std::vector<Real>& x, Real& value);

template<typename Real>
extern std::vector<Real> interp1(std::vector<Real>& x, std::vector<Real>& y, std::vector<Real>& x_new);

extern std::vector<complex_t> ComplexInterp(std::vector<float> x, std::vector<complex_t> y, std::vector<float> xnew);

#endif //head file
