#include "BinomialDynamic.hpp"

BinomialDynamic::BinomialDynamic(size_t _N) : N(_N), lattice(N) {}

double BinomialDynamic::getRiskNeutralProbability() const {
    return riskNeutralProbability;
}

size_t BinomialDynamic::getN() const { return N; }

BinomialLattice<double> BinomialDynamic::getLattice() const { return lattice; }

double convertToR(const RiskFreeRateFlat &rfr,
                  const BinomialParametersVolGrid &binomial_params) {
    double r = rfr(0, 0);

    double dt = binomial_params.getDeltaT();
    return std::exp(r * dt) - 1;
}

StockDynamic::StockDynamic(size_t size, const Stock &_stock,
                           const RiskFreeRateFlat &_rfr,
                           const BinomialParametersNoVol &binomial_params)
    : BinomialDynamic(size),
      stock(_stock),
      riskFreeRateFlat(_rfr),
      model(binomial_params) {
    double d = model.getD();
    double u = model.getU();
    double c = stock.getDivYield();
    riskNeutralProbability = (_rfr(0, 0) - (d + c)) / (u - d);
    buildLattice();
}

StockDynamic::StockDynamic(size_t size, const Stock &_stock,
                           const RiskFreeRateFlat &_rfr,
                           const BinomialParametersVolGrid &binomial_params)
    : BinomialDynamic(size),
      stock(_stock),
      riskFreeRateFlat(convertToR(_rfr, binomial_params)),
      model(binomial_params) {
    assert(size == binomial_params.getN());
    double d = model.getD();
    double u = model.getU();
    double c = stock.getDivYield();

    double dt = binomial_params.getDeltaT();

    double R = std::exp((_rfr(0, 0) - c) * dt) - 1;

    riskNeutralProbability = (R - d) / (u - d);
    buildLattice();
}

void StockDynamic::buildLattice() {
    if (lattice_built) return;

    lattice[0][0] = stock.getSpot();
    double d = model.getD();
    double u = model.getU();

    for (size_t i = 1; i <= N; i++) {
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
    return riskFreeRateFlat(0, 0);  // we assumed rfr constant
}

FuturesDynamic::FuturesDynamic(size_t fut_mat, BinomialDynamic &_primaryAsset)
    : BinomialDynamic(fut_mat), primaryAsset(_primaryAsset), maturity(fut_mat) {
    assert(fut_mat <= primaryAsset.getN());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double FuturesDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

void FuturesDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability;

    BinomialLattice<double> primaryLattice = primaryAsset.getLattice();

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