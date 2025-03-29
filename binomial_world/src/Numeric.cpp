#include "Numeric.hpp"

#include <cassert>

Numeric::Numeric(double newValue) : value(newValue) {}

double Numeric::operator()() const { return value; }

void Numeric::operator()(double newValue) {
    assert(newValue >= 0.);
    value = newValue;
}

Spot::Spot(double newValue) : Numeric(newValue) { assert(newValue > 0.); }

DividendYield::DividendYield(double newValue) : Numeric(newValue) {
    assert(newValue >= 0. && newValue < 1.);
}

Probability::Probability(double newValue) : Numeric(newValue) {
    assert(newValue >= 0. && newValue <= 1.);
}

Strike::Strike(double newValue) : Numeric(newValue) { assert(newValue >= 0.); }

Coupon::Coupon(double _value) : Numeric(_value) { assert(_value > 0.); }

FaceValue::FaceValue(double _value) : Numeric(_value) { assert(_value > 0.); }