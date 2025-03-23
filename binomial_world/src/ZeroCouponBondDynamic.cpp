#include "ZeroCouponBondDynamic.hpp"

ZeroCouponBondDynamic::ZeroCouponBondDynamic(
    size_t _maturity, RiskFreeRateTermStructure &_primaryAsset,
    double _faceValue)
    : BinomialDynamic(_maturity),
      maturity(_maturity),
      primaryAsset(_primaryAsset),
      faceValue(_faceValue) {
    assert(maturity <= primaryAsset.getN());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double ZeroCouponBondDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

void ZeroCouponBondDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability;

    for (int i = 0; i <= maturity; ++i) {
        lattice[maturity][i] = faceValue;
    }

    for (int n = maturity - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double discount_n_i = 1. / (1 + getRFR(n, i));

            lattice[n][i] =
                (q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i]) *
                discount_n_i;
        }
    }
    lattice_built = true;
}

double ZeroCouponBondDynamic::price() const {
    assert(lattice_built);
    return lattice[0][0];
}