#include "refactoring_13.hpp"

namespace new_code {

Call::Call(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

Put::Put(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

double Call::payoff(double z) const { return std::max(z - getK(), 0.); }

double Put::payoff(double z) const { return std::max(getK() - z, 0.); }

}  // namespace new_code
