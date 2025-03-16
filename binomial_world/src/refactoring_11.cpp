#include "refactoring_11.hpp"

namespace new_code {

Futures::Futures(BinomialModelDynamic &modelDynamic)
    : BinomialModelDynamic(modelDynamic.getN()),
      q(modelDynamic.getRiskNeutralProbability()),
      u(modelDynamic.getU()),
      r(modelDynamic.getRiskFreeRate()),
      d(modelDynamic.getD()),
      N(modelDynamic.getN()) {
    modelDynamic.buildLattice();
    lattice = modelDynamic.getLattice();
}

void Futures::buildLattice() {
    if (lattice_built) return;

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            lattice(n, i,
                    q * lattice(n + 1, i + 1) + (1. - q) * lattice(n + 1, i));
        }
    }
    lattice_built = true;
}

double Futures::getRiskFreeRate() const { return r; }
double Futures::getRiskNeutralProbability() const { return q; }
size_t Futures::getN() const { return N; }
double Futures::getU() const { return u; }
double Futures::getD() const { return d; }

double Futures::price() {
    assert(lattice_built);
    return lattice(0, 0);
}

}  // namespace new_code