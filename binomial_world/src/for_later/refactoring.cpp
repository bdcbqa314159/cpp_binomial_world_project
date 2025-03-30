#include "refactoring.hpp"  // IWYU pragma: keep

#include <cassert>
#include <cmath>
#include <cstddef>

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
    assert(newValue >= 0.);
}

NegativeReal::NegativeReal(double newValue) : RealValue(newValue) {
    assert(newValue <= 0);
}

Volatility::Volatility(double newValue) : PositiveReal(newValue) {}

StockSpot::StockSpot(double newValue) : PositiveReal(newValue) {
    assert(newValue > 0);
}

RateSpot::RateSpot(double newValue) : RealValue(newValue) {}

UpFactor::UpFactor(double newValue) : PositiveReal(newValue) {
    assert(newValue < 1. && newValue > 0.);
}

DownFactor::DownFactor(double newValue) : NegativeReal(newValue) {
    assert(newValue > -1. && newValue < 0.);
}

Periods::Periods(size_t newValue) : PositiveInteger(newValue) {}

Size::Size(size_t newValue) : IntegerValue(newValue) {}

TimeToMaturity::TimeToMaturity(double newValue) : PositiveReal(newValue) {}

MaturityInPeriods::MaturityInPeriods(size_t newValue)
    : PositiveInteger(newValue) {}

DividendYield::DividendYield(double newValue) : PositiveReal(newValue) {}

ShortRateSpot::ShortRateSpot(double newValue) : RealValue(newValue) {}

Probability::Probability(double newValue) : RealValue(newValue) {
    assert(newValue >= 0. && newValue <= 1.);
}

Strike::Strike(double newValue) : PositiveReal(newValue) {}

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
    return std::exp(sigma() * std::sqrt(dt)) - 1;
}

double BinomialParametersVolGrid::getD() const {
    double u = getU();
    return getDownFactor(u);
}

}  // namespace binomial_parameters

namespace binomial_model {

BinomialModel::BinomialModel(double u, double d) : U(u), D(d) {}

BinomialModel::BinomialModel(
    const binomial_parameters::BinomialParameters &params)
    : U(params.getU()), D(params.getD()) {}

double BinomialModel::getU() const { return U(); }
double BinomialModel::getD() const { return D(); }

}  // namespace binomial_model

namespace binomial_equities {

using namespace binomial_values;

Stock::Stock(double _spot, double _div_yield)
    : spot(_spot), div_yield(_div_yield) {}

double Stock::getDivYield() const { return div_yield(); }
double Stock::getSpot() const { return spot(); }

void Stock::setDivYield(double _div_yield) { div_yield(_div_yield); }
void Stock::setSpot(double _spot) { spot(_spot); }
}  // namespace binomial_equities

namespace binomial_interest_rates {

using namespace binomial_values;

ShortRate::ShortRate(double _spot) : spot(_spot) {}
double ShortRate::getSpot() const { return spot(); }
void ShortRate::setSpot(double _spot) { spot(_spot); }

}  // namespace binomial_interest_rates

namespace binomial_dynamic {

using namespace binomial_values;
using namespace binomial_model;
using namespace binomial_equities;
using namespace binomial_interest_rates;
using namespace binomial_parameters;
using namespace binomial_lattice;

BinomialDynamic::BinomialDynamic()
    : N(0), riskNeutralProbability(1.), lattice(0) {}

BinomialDynamic::BinomialDynamic(size_t newN)
    : N(newN), riskNeutralProbability(0.), lattice(newN) {}

double BinomialDynamic::getRiskNeutralProbability() const {
    return riskNeutralProbability();
}

size_t BinomialDynamic::getN() const { return N(); }

const BinomialLatticeNumeric &BinomialDynamic::getLattice() const {
    return lattice;
}

RiskFreeRateFlat::RiskFreeRateFlat(double _spot)
    : BinomialDynamic(), shortRate(_spot) {
    riskNeutralProbability(1.);
    buildLattice();
}

double RiskFreeRateFlat::getRFR(size_t i, size_t j) const {
    assert(i <= j);
    return shortRate.getSpot();
}

void RiskFreeRateFlat::buildLattice() {
    lattice[0][0] = shortRate.getSpot();
    lattice_built = true;
}

StockDynamic::StockDynamic(
    size_t newN, const binomial_equities::Stock &newStock,
    const binomial_dynamic::RiskFreeRateFlat &newRiskFreeRateFlat,
    const binomial_parameters::BinomialParametersNoVol &params)
    : BinomialDynamic(newN),
      stock(newStock),
      riskFreeRateFlat(newRiskFreeRateFlat),
      model(params) {
    double u = model.getU();
    double d = model.getD();
    double div_yield = stock.getDivYield();
    double r = riskFreeRateFlat.getRFR(0, 0);

    riskNeutralProbability((r - (d + div_yield)) / (u - d));

    buildLattice();
}

StockDynamic::StockDynamic(
    size_t newN, const binomial_equities::Stock &newStock,
    const binomial_dynamic::RiskFreeRateFlat &newRiskFreeRateFlat,
    const binomial_parameters::BinomialParametersVolGrid &params)
    : BinomialDynamic(newN),
      stock(newStock),
      riskFreeRateFlat(newRiskFreeRateFlat),
      model(params) {
    double u = model.getU();
    double d = model.getD();
    double div_yield = stock.getDivYield();
    double r = riskFreeRateFlat.getRFR(0, 0);

    double newR = std::exp(r * params.getDeltaT()) - 1;
    riskFreeRateFlat = RiskFreeRateFlat(newR);

    double dt = params.getDeltaT();

    double R = std::exp((r - div_yield) * dt) - 1;

    riskNeutralProbability((R - d) / (u - d));

    buildLattice();
}

void StockDynamic::buildLattice() {
    if (lattice_built) return;

    lattice[0][0] = stock.getSpot();
    double d = model.getD();
    double u = model.getU();

    for (size_t i = 1; i <= N(); i++) {
        for (size_t j = 0; j < i + 1; j++) {
            if (j == 0)
                lattice[i][j] = lattice[i - 1][j] * (1. + d);
            else
                lattice[i][j] = lattice[i - 1][j - 1] * (1. + u);
        }
    }
    lattice_built = true;
}

double StockDynamic::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return riskFreeRateFlat.getRFR(0, 0);
}

}  // namespace binomial_dynamic

namespace binomial_options {

using namespace binomial_values;
using namespace binomial_lattice;
using namespace binomial_dynamic;

Option::Option(size_t newMaturity) : maturity(newMaturity) {}
size_t Option::getMaturity() const { return maturity(); }

EurOption::EurOption(size_t newMaturity) : Option(newMaturity) {}

double EurOption::priceByCRR(BinomialDynamic &modelDynamic) const {
    double q = modelDynamic.getRiskNeutralProbability();
    assert(maturity() <= modelDynamic.getN());
    BinomialLatticeNumeric lattice = modelDynamic.getLattice();

    size_t N = maturity();

    std::vector<double> prices(N + 1);
    for (size_t i = 0; i <= N; ++i) {
        prices[i] = payoff(lattice[N][i]);
    }

    for (int n = N - 1; n >= 0; --n) {
        for (size_t i = 0; i <= n; ++i) {
            double rfr_n_i = modelDynamic.getRFR(n, i);
            double discount_n_i = 1. / (1. + rfr_n_i);

            prices[i] =
                discount_n_i * (q * prices[i + 1] + (1 - q) * prices[i]);
        }
    }

    return prices[0];
}

AmOption::AmOption(size_t newMaturity)
    : Option(newMaturity), priceTree(maturity()), stoppingTree(maturity()) {}

double AmOption::priceBySnell(BinomialDynamic &modelDynamic) {
    double q = modelDynamic.getRiskNeutralProbability();

    assert(maturity() <= modelDynamic.getN());

    double continuationValue{};

    BinomialLatticeNumeric lattice = modelDynamic.getLattice();
    size_t N = maturity();

    for (int i = 0; i <= N; i++) {
        priceTree[N][i] = payoff(lattice[N][i]);
        stoppingTree[N][i] = true;
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double rfr_n_i = modelDynamic.getRFR(n, i);
            double discount_n_i = 1. / (1. + rfr_n_i);

            continuationValue = discount_n_i * (q * priceTree[n + 1][i + 1] +
                                                (1. - q) * priceTree[n + 1][i]);

            priceTree[n][i] = payoff(lattice[n][i]);
            stoppingTree[n][i] = true;

            if (continuationValue > priceTree[n][i]) {
                priceTree[n][i] = continuationValue;
                stoppingTree[n][i] = false;
            } else if (priceTree[n][i] == 0.) {
                stoppingTree[n][i] = false;
            }
        }
    }
    return priceTree[0][0];
}

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

}  // namespace binomial_options

namespace binomial_dynamic {

FuturesDynamic::FuturesDynamic(size_t fut_mat, BinomialDynamic &_primaryAsset)
    : BinomialDynamic(fut_mat), primaryAsset(_primaryAsset), maturity(fut_mat) {
    assert(maturity() <= primaryAsset.getN());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double FuturesDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

void FuturesDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();

    BinomialLatticeNumeric primaryLattice = primaryAsset.getLattice();

    size_t N = maturity();

    for (int i = 0; i <= N; ++i) {
        lattice[N][i] = primaryLattice[N][i];
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            lattice[n][i] =
                q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i];
        }
    }

    lattice_built = true;
}

double FuturesDynamic::price() const {
    assert(lattice_built);
    return lattice[0][0];
}
}  // namespace binomial_dynamic