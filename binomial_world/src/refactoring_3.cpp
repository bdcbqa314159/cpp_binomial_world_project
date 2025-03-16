#include "refactoring_3.hpp"

#include <cassert>

namespace new_code {

BinomialDirections::BinomialDirections(double _U) : U(_U) {
    assert(-1. < U && U < 1.);
    D = -U / (1. + U);
}

double BinomialDirections::getU() const { return U; }
double BinomialDirections::getD() const { return D; }

}  // namespace new_code