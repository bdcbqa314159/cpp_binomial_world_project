#include "BinomialModelFutures.hpp"

BinomialModelFutures::BinomialModelFutures(BinomialModel &primaryAssetModel)
    : BinomialModel(primaryAssetModel.getN()) {
    riskNeutralProbability = primaryAssetModel.getRiskNeutralProbability();
    riskFreeRate = primaryAssetModel.getRiskFreeRate();
    lattice = primaryAssetModel.getLattice();
}

void BinomialModelFutures::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability;

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            lattice[n][i] =
                q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i];
        }
    }
    lattice_built = true;
}

double BinomialModelFutures::price() {
    buildLattice();
    return lattice[0][0];
}