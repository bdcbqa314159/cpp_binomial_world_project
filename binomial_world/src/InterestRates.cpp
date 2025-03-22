#include "InterestRates.hpp"

RiskFreeRate::RiskFreeRate(double _spot) : spot(_spot) {}

RiskFreeRateFlat::RiskFreeRateFlat(double _spot) : RiskFreeRate(_spot) {}

double RiskFreeRateFlat::operator()(size_t, size_t) const { return spot(); }
