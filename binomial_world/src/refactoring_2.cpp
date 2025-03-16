#include <cassert>

#include "refactoring_2.hpp"

namespace new_code {

PrimaryAsset::PrimaryAsset(double _spot) : spot(_spot) {}
double PrimaryAsset::getSpot() const { return spot; }
void PrimaryAsset::setSpot(double _spot) { spot = _spot; }

InterestRate::InterestRate(double _spot) : PrimaryAsset(_spot) {}

IRFlat::IRFlat(double _spot) : InterestRate(_spot) {}

double IRFlat::getR() const { return getSpot(); }
void IRFlat::setR(double _r) { setSpot(_r); }

IRTermStructure::IRTermStructure(double _spot) : InterestRate(_spot) {}

RiskFreeRateFlat::RiskFreeRateFlat(double _spot) : IRFlat(_spot) {}

RiskFreeRateTerm::RiskFreeRateTerm(double _spot) : IRTermStructure(_spot) {}

Stock::Stock(double _spot, double _div_yield)
    : PrimaryAsset(_spot), div_yield(_div_yield) {
    assert(spot > 0.);
    assert(0. <= div_yield && div_yield < 1.);
}

double Stock::getDivYield() const { return div_yield; }
void Stock::setDivYield(double _div_yield) { div_yield = _div_yield; }

}  // namespace new_code