#include "BinomialModelEquities.hpp"

BinomialModelStock::BinomialModelStock(const Stock &_stock,
                                       const BinomialDirections &_model,
                                       const BSDirections &_coefficients)
    : BinomialModel(_model.getN()),
      stock(_stock),
      model(_model),
      coefficients(_coefficients) {
    double d = model.getD();
    double u = model.getU();
    double c = stock.getDivYield();
    assert(d < coefficients.getR() && coefficients.getR() < u);
    riskNeutralProbability = (coefficients.getR() - (d + c)) / (u - d);
    riskFreeRate = coefficients.getR();
    buildLattice();
}

BinomialModelStock::BinomialModelStock(const Stock &_stock,
                                       const BSDirections &_directions)
    : BinomialModel(_directions.getN()),
      stock(_stock),
      model(_directions.getU(), _directions.getN()),
      coefficients(_directions) {
    double dt = coefficients.getT() / coefficients.getN();
    double div_yield = stock.getDivYield();
    double r_bs = coefficients.getR();

    double d = model.getD();
    double u = model.getU();
    double R = std::exp((r_bs - div_yield) * dt) - 1.;

    riskFreeRate = std::exp(r_bs * dt) - 1.;
    riskNeutralProbability = (R - d) / (u - d);
    buildLattice();
}

void BinomialModelStock::buildLattice() {
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