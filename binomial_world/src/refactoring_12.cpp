#include "refactoring_12.hpp"

namespace new_code {

SingleStrike::SingleStrike(size_t newN, double newK)
    : Option(newN), EurOption(newN), AmOption(newN) {
    assert(newK > 0);
    K = newK;
}

double SingleStrike::getK() const { return K; }
}  // namespace new_code
