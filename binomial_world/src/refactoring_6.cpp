#include "refactoring_6.hpp"

#include <cassert>

namespace new_code {

BinomialModelStock::BinomialModelStock(const Stock &_stock, double _U,
                                       size_t _N, double _r)
    : stock(_stock), model(stock.getSpot(), _U, _N), riskFreeRate(_r) {
    double d = model.getD();
    double u = model.getU();
    double c = stock.getDivYield();
    assert(d < riskFreeRate && riskFreeRate < u);
    riskNeutralProbability = (riskFreeRate - (d + c)) / (u - d);
}

double BinomialModelStock::getRiskNeutralProbability() const {
    return riskNeutralProbability;
}

double BinomialModelStock::getRiskFreeRate() const { return riskFreeRate; }

size_t BinomialModelStock::getN() const { return model.getN(); }
double BinomialModelStock::getU() const { return model.getU(); }
double BinomialModelStock::getD() const { return model.getD(); }
double BinomialModelStock::initial_value() const { return stock.getSpot(); }

}  // namespace new_code