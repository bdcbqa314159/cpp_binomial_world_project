#include "BinomialValues.hpp"

#include <cassert>

namespace binomial_values {

IntegerValue::IntegerValue(size_t newValue) : Value(newValue) {}

RealValue::RealValue(double newValue) : Value(newValue) {}

PositiveInteger::PositiveInteger(size_t newValue) : IntegerValue(newValue) {
    assert(newValue > 0);
}

PositiveReal::PositiveReal(double newValue) : RealValue(newValue) {
    assert(newValue > 0);
}

NegativeReal::NegativeReal(double newValue) : RealValue(newValue) {
    assert(newValue < 0);
}

Volatility::Volatility(double newValue) : PositiveReal(newValue) {}

StockSpot::StockSpot(double newValue) : PositiveReal(newValue) {}

RateSpot::RateSpot(double newValue) : RealValue(newValue) {}

UpFactor::UpFactor(double newValue) : PositiveReal(newValue) {
    assert(newValue < 1.);
}

DownFactor::DownFactor(double newValue) : NegativeReal(newValue) {
    assert(newValue > -1.);
}

Periods::Periods(size_t newValue) : PositiveInteger(newValue) {}

Size::Size(size_t newValue) : PositiveInteger(newValue) {}

}  // namespace binomial_values
