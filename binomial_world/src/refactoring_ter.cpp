#include "refactoring_ter.hpp"  // IWYU pragma: keep

#include <cassert>

namespace new_code_bis {

// BinomialDirections::BinomialDirections(double newU) : u(newU) {
//     assert(0. < u);
//     d = 1 / u;
// }

// BinomialDirections::BinomialDirections(double newU, double newD)
//     : u(newU), d(newD) {
//     assert(0. < d && d < u);
// }

// double BinomialDirections::getU() const { return u; }
// double BinomialDirections::getD() const { return d; }

// void BinomialDirections::setDirections(double newU, double newD) {
//     u = newU;
//     d = newD;

//     assert(0. < d && d < u);
// }

// BinomialVolGrid::BinomialVolGrid(double newSigma, double newTimeToMaturity,
//                                  size_t newPeriods)
//     : sigma(newSigma), timeToMaturity(newTimeToMaturity), periods(newPeriods)
//     { assert(sigma > 0. && timeToMaturity > 0. && periods > 0);
// }

// double BinomialVolGrid::getSigma() const { return sigma; }
// double BinomialVolGrid::getTimeToMaturity() const { return timeToMaturity; }
// size_t BinomialVolGrid::getPeriods() const { return periods; }

// double BinomialVolGrid::getDeltaT() const { return timeToMaturity / periods;
// }

void latticeBuilder(double initial_value, double u, double d, size_t periods,
                    BinomialLattice<double> &lattice) {
    lattice[0][0] = initial_value;

    for (size_t i = 1; i <= periods; i++) {
        for (size_t j = 0; j < i + 1; j++) {
            if (j == 0)
                lattice[i][j] = lattice[i - 1][j] * d;
            else
                lattice[i][j] = lattice[i - 1][j - 1] * u;
        }
    }
}

VolGridAdapter::VolGridAdapter(const BinomialVolGrid &newVolGrid)
    : volGrid(newVolGrid) {
    double dt = getDeltaT();
    double sigma = volGrid.getSigma();
    double u = std::exp(sigma * std::sqrt(dt));
    double d = 1 / u;

    setDirections(u, d);
}

double VolGridAdapter::getSigma() const { return volGrid.getSigma(); }
double VolGridAdapter::getTimeToMaturity() const {
    return volGrid.getTimeToMaturity();
}
size_t VolGridAdapter::getPeriods() const { return volGrid.getPeriods(); }
double VolGridAdapter::getDeltaT() const { return volGrid.getDeltaT(); }

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

Stock::Stock(double newSpot, double newDivYield)
    : spot(newSpot), div_yield(newDivYield) {}

double Stock::getDivYield() const { return div_yield(); }
double Stock::getSpot() const { return spot(); }

void Stock::setDivYield(double newDivYield) { div_yield(newDivYield); }

void Stock::setSpot(double newSpot) { spot(newSpot); }

ShortRate::ShortRate(double newSpot) : spot(newSpot) {}

double ShortRate::getSpot() const { return spot(); }
void ShortRate::setSpot(double newSpot) { spot(newSpot); }

BinomialDynamic::BinomialDynamic(size_t newPeriods)
    : periods(newPeriods), lattice(newPeriods) {}

double BinomialDynamic::getRiskNeutralProbability() const {
    return riskNeutralProbability();
}

size_t BinomialDynamic::getPeriods() const { return periods; }

const BinomialLattice<double> &BinomialDynamic::getLattice() const {
    return lattice;
}

RiskFreeRateFlat::RiskFreeRateFlat(double newSpot)
    : BinomialDynamic(), shortRate(newSpot) {
    buildLattice();
}

double RiskFreeRateFlat::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return shortRate.getSpot();
}

void RiskFreeRateFlat::buildLattice() {
    lattice[0][0] = shortRate.getSpot();
    lattice_built = true;
}

StockDynamic::StockDynamic(size_t newPeriods, const Stock &newStock,
                           const RiskFreeRateFlat &newRiskFreeRateFlat,
                           const BinomialDirections &newModel)
    : BinomialDynamic(newPeriods),
      stock(newStock),
      riskFreeRateFlat(newRiskFreeRateFlat),
      model(newModel) {
    double u = model.getU();
    double d = model.getD();
    double div_yield = stock.getDivYield();
    // The logic of this is in the resolution of the Exercise 2.10 of the book
    // Stochastic Calculus for Finance I: The Binomial Asset Pricing Model
    model.setDirections(u * (1 - div_yield), d * (1 - div_yield));

    double r = riskFreeRateFlat.getRFR(0, 0);

    riskNeutralProbability((1 + r - model.getD()) /
                           (model.getU() - model.getD()));

    buildLattice();
}

StockDynamic::StockDynamic(size_t newPeriods, const Stock &newStock,
                           const RiskFreeRateFlat &newRiskFreeRateFlat,
                           const VolGridAdapter &params)
    : BinomialDynamic(newPeriods),
      stock(newStock),
      riskFreeRateFlat(newRiskFreeRateFlat) {
    double u = params.getU();
    double d = params.getD();
    double div_yield = stock.getDivYield();
    double r = riskFreeRateFlat.getRFR(0, 0);

    double newR = std::exp(r * params.getDeltaT()) - 1;
    riskFreeRateFlat = RiskFreeRateFlat(newR);

    double dt = params.getDeltaT();

    double r_cont = std::exp((r - div_yield) * dt);

    riskNeutralProbability((r_cont - d) / (u - d));
    model.setDirections(u, d);

    buildLattice();
}

void StockDynamic::buildLattice() {
    if (lattice_built) return;

    double initial_value = stock.getSpot();

    latticeBuilder(initial_value, model.getU(), model.getD(), periods, lattice);

    lattice_built = true;
}

double StockDynamic::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return riskFreeRateFlat.getRFR(0, 0);
}

FuturesDynamic::FuturesDynamic(size_t fut_mat, BinomialDynamic &_primaryAsset)
    : BinomialDynamic(fut_mat), primaryAsset(_primaryAsset), maturity(fut_mat) {
    assert(maturity <= primaryAsset.getPeriods());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double FuturesDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

void FuturesDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();
    BinomialLattice<double> primaryLattice = primaryAsset.getLattice();
    size_t N = maturity;

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

Strike::Strike(double newValue) : Numeric(newValue) { assert(newValue >= 0.); }

Option::Option(size_t newMaturity) : maturity(newMaturity) {}
size_t Option::getMaturity() const { return maturity; }

EurOption::EurOption(size_t newMaturity) : Option(newMaturity) {}

double EurOption::priceByCRR(BinomialDynamic &modelDynamic) const {
    double q = modelDynamic.getRiskNeutralProbability();
    assert(maturity <= modelDynamic.getPeriods());
    BinomialLattice<double> lattice = modelDynamic.getLattice();

    size_t N = maturity;

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
    : Option(newMaturity), priceTree(newMaturity), stoppingTree(newMaturity) {}

double AmOption::priceBySnell(BinomialDynamic &modelDynamic) {
    double q = modelDynamic.getRiskNeutralProbability();

    assert(maturity <= modelDynamic.getPeriods());

    double continuationValue{};

    BinomialLattice<double> lattice = modelDynamic.getLattice();

    size_t N = maturity;

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

}  // namespace new_code_bis