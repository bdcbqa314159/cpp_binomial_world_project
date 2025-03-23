#include "RiskFreeRateTermStructure.hpp"

RiskFreeRateTermStructure::RiskFreeRateTermStructure(
    double _spot, size_t _N, const BinomialParametersNoVol &_params)
    : RiskFreeRate(_spot), BinomialDynamic(_N), model(_params) {
    riskNeutralProbability = 0.5;
    buildLattice();
}

void RiskFreeRateTermStructure::buildLattice() {
    if (lattice_built) return;

    lattice[0][0] = spot();
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

double RiskFreeRateTermStructure::operator()(size_t i, size_t j) const {
    assert(lattice_built);
    return lattice[i][j];
}

double RiskFreeRateTermStructure::getRFR(size_t i, size_t j) const {
    return operator()(i, j);
}