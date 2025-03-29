#include "refactoring_ter.hpp"  // IWYU pragma: keep

#include <cassert>

namespace new_code_bis {

SingleStrike::SingleStrike(size_t newMaturity, double newK)
    : Option(newMaturity),
      EurOption(newMaturity),
      AmOption(newMaturity),
      K(newK) {}

double SingleStrike::getK() const { return K(); }

Call::Call(size_t newMaturity, double newK)
    : Option(newMaturity), SingleStrike(newMaturity, newK) {}

Put::Put(size_t newMaturity, double newK)
    : Option(newMaturity), SingleStrike(newMaturity, newK) {}

double Call::payoff(double z) const { return std::max(z - K(), 0.); }

double Put::payoff(double z) const { return std::max(K() - z, 0.); }

}  // namespace new_code_bis