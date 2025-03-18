#include "BinomialDirections.hpp"

#include <cassert>

BinomialDirections::BinomialDirections(double _U, size_t _N) : U(_U), N(_N) {
    assert(-1. < U && U < 1.);
    D = -U / (1. + U);
}

double BinomialDirections::getU() const { return U; }
double BinomialDirections::getD() const { return D; }
size_t BinomialDirections::getN() const { return N; }