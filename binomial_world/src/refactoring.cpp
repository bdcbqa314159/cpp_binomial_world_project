#include "refactoring.hpp"

namespace new_code {

RiskFreeRate::RiskFreeRate(double _spot) : spot(_spot) {}
RiskFreeRateFlat::RiskFreeRateFlat(double _spot) : RiskFreeRate(_spot) {}
double RiskFreeRateFlat::operator()(size_t, size_t) const { return spot(); }

BinomialDynamic::BinomialDynamic(size_t _N) : N(_N), lattice(N) {}

double BinomialDynamic::getRiskNeutralProbability() const {
    return riskNeutralProbability;
}

size_t BinomialDynamic::getN() const { return N; }

StockDynamic::StockDynamic(const Stock &_stock, const RiskFreeRateFlat &_rfr,
                           const BinomialDirections &_model)
    : BinomialDynamic(_model.getN()),
      stock(_stock),
      riskFreeRateFlat(_rfr),
      model(_model) {
    double d = model.getD();
    double u = model.getU();
    double c = stock.getDivYield();
    riskNeutralProbability = (_rfr(0, 0) - (d + c)) / (u - d);
    buildLattice();
}

BinomialLattice<double> BinomialDynamic::getLattice() const { return lattice; }

void StockDynamic::buildLattice() {
    if (lattice_built) return;
    size_t N = model.getN();

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
    return riskFreeRateFlat(i, j);
}
}  // namespace new_code
