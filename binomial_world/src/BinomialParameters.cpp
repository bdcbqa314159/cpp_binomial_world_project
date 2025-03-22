#include "BinomialParameters.hpp"

#include <cassert>
#include <cmath>

BinomialParametersNoVol::BinomialParametersNoVol(double _U) : U(_U) {
    assert(-1. < U && U < 1.);
    D = -U / (1. + U);
}

BinomialParametersNoVol::BinomialParametersNoVol(double _U, double _D)
    : U(_U), D(_D) {
    assert(0 < D && D < 1.);
    assert(0 < U && U < 1.);
    D = -D;
}

double BinomialParametersNoVol::getU() const { return U; }
double BinomialParametersNoVol::getD() const { return D; }

BinomialParametersVolGrid::BinomialParametersVolGrid(double _sigma, double _T,
                                                     size_t _N)
    : sigma(_sigma), T(_T), N(_N) {
    assert(sigma > 0 && T > 0 && N > 0);
}

double BinomialParametersVolGrid::getSigma() const { return sigma; }
double BinomialParametersVolGrid::getT() const { return T; }
size_t BinomialParametersVolGrid::getN() const { return N; }

double BinomialParametersVolGrid::getDeltaT() const { return T / N; }

double BinomialParametersVolGrid::getU() const {
    return std::exp(sigma * std::sqrt(T / N)) - 1;
}

double BinomialParametersVolGrid::getD() const {
    double U = getU();
    return -U / (1. + U);
}