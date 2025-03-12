#include "SingleStrikeOptions.hpp"

SingleStrike::SingleStrike(size_t newN, double newK) : Option(newN), EurOption(newN), AmOption(newN)
{
    assert(newK > 0);
    K = newK;
}

Call::Call(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

Put::Put(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

double Call::payoff(double z) const
{
    return std::max(z - getK(), 0.);
}

double Put::payoff(double z) const
{
    return std::max(getK() - z, 0.);
}