#include "refactoring_6.hpp"

#include <cassert>

namespace new_code {

BinomialModelStock::BinomialModelStock(const Stock &_stock, double _U,
                                       size_t _N, double _r)
    : BinomialModelDynamic(_N),
      stock(_stock),
      model(stock.getSpot(), _U, _N),
      riskFreeRate(_r) {
    double d = model.getD();
    double u = model.getU();
    double c = stock.getDivYield();
    assert(d < riskFreeRate && riskFreeRate < u);
    riskNeutralProbability = (riskFreeRate - (d + c)) / (u - d);
}

void BinomialModelStock::buildLattice() {
    if (lattice_built) return;

    double U = getU();
    double D = getD();
    // double S0 = initial_value();

    lattice(0, 0) = stock.getSpot();

    for (size_t i = 1; i <= getN(); i++) {
        for (size_t j = 0; j < i + 1; j++) {
            if (j == 0)
                lattice(i, j) = lattice(i - 1, j) * (1. + D);
            else if (j == i)
                lattice(i, j) = lattice(i - 1, j - 1) * (1. + U);
            else
                lattice(i, j) = lattice(i - 1, j - 1) * (1. + U);
        }
    }
    lattice_built = true;
}

double BinomialModelStock::getRiskNeutralProbability() const {
    return riskNeutralProbability;
}

double BinomialModelStock::getRiskFreeRate() const { return riskFreeRate; }

size_t BinomialModelStock::getN() const { return model.getN(); }
double BinomialModelStock::getU() const { return model.getU(); }
double BinomialModelStock::getD() const { return model.getD(); }
// double BinomialModelStock::initial_value() const { return stock.getSpot(); }

}  // namespace new_code