#if 0
#include "BinomialDirections.hpp"

#include <cassert>

BinomialDirections::BinomialDirections(double _U, size_t _N) : U(_U), N(_N) {
    assert(-1. < U && U < 1.);
    D = -U / (1. + U);
}

// we need to check the when the tree is not recombining
BinomialDirections::BinomialDirections(double _U, double _D, size_t _N)
    : U(_U), D(_D), N(_N) {
    assert(0 < D && D < 1.);
    assert(0 < U && U < 1.);
    D = -D;
}

double BinomialDirections::getU() const { return U; }
double BinomialDirections::getD() const { return D; }
size_t BinomialDirections::getN() const { return N; }
#endif