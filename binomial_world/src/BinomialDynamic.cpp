#include "BinomialDynamic.hpp"

#include "Utils.hpp"

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