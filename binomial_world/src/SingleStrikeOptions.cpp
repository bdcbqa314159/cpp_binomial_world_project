#include "SingleStrikeOptions.hpp"

// SingleStrike::SingleStrike(size_t newN, double newK)
//     : Option(newN), EurOption(newN), AmOption(newN), K(newK) {}

// double SingleStrike::getK() const { return K; }

// Call::Call(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK)
// {}

// Put::Put(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK)
// {}

// double Call::payoff(double z) const { return std::max(z - getK(), 0.); }

// double Put::payoff(double z) const { return std::max(getK() - z, 0.); }

SingleStrike::SingleStrike(size_t newN, double newK)
    : Option(newN), EurOption(newN), AmOption(newN), K(newK) {}

double SingleStrike::getK() const { return K; }

Call::Call(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

Put::Put(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

double Call::payoff(double z) const { return std::max(z - getK(), 0.); }

double Put::payoff(double z) const { return std::max(getK() - z, 0.); }
