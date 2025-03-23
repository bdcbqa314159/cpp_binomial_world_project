#include "refactoring.hpp"  // IWYU pragma: keep

#include <cassert>
#include <cmath>

namespace binomial_lattice {

BinomialLatticeNumeric::BinomialLatticeNumeric(size_t newN)
    : BinomialLattice(newN) {}

BinomialLatticeBoolean::BinomialLatticeBoolean(size_t newN)
    : BinomialLattice(newN) {}

}  // namespace binomial_lattice

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

TimeToMaturity::TimeToMaturity(double newValue) : PositiveReal(newValue) {}

MaturityInPeriods::MaturityInPeriods(size_t newValue)
    : PositiveInteger(newValue) {}

}  // namespace binomial_values

namespace binomial_parameters {

using namespace binomial_values;

double getDownFactor(double up) { return -up / (1 + up); }

DownFactor getDownFactor(const UpFactor &up) {
    double u = up();
    double d = -u / (1 + u);
    return DownFactor(d);
}

BinomialParametersNoVol::BinomialParametersNoVol(double u)
    : U(u), D(getDownFactor(U)){};

BinomialParametersNoVol::BinomialParametersNoVol(double u, double d)
    : U(u), D(d) {}

double BinomialParametersNoVol::getU() const { return U(); }
double BinomialParametersNoVol::getD() const { return D(); }

BinomialParametersVolGrid::BinomialParametersVolGrid(double sigma, double T,
                                                     size_t N)
    : sigma(sigma), T(T), N(N) {}

double BinomialParametersVolGrid::getSigma() const { return sigma(); }
double BinomialParametersVolGrid::getT() const { return T(); }
size_t BinomialParametersVolGrid::getN() const { return N(); }

double BinomialParametersVolGrid::getDeltaT() const { return T() / N(); }

double BinomialParametersVolGrid::getU() const {
    double dt = getDeltaT();
    return std::exp(sigma() * dt) - 1;
}

double BinomialParametersVolGrid::getD() const {
    double u = getU();
    return getDownFactor(u);
}

}  // namespace binomial_parameters