#include "refactoring.hpp"

#include <cstddef>

namespace new_code {

BinomialDirections_new::BinomialDirections_new(double _U) : U(_U) {
    assert(-1. < U && U < 1.);
    D = -U / (1. + U);
}

// we need to check the when the tree is not recombining
BinomialDirections_new::BinomialDirections_new(double _U, double _D)
    : U(_U), D(_D) {
    assert(0 < D && D < 1.);
    assert(0 < U && U < 1.);
    D = -D;
}

double BinomialDirections_new::getU() const { return U; }
double BinomialDirections_new::getD() const { return D; }

double convertToU(double sigma, double T, size_t N) {
    assert(sigma > 0);
    assert(T > 0);
    assert(N > 0);

    return std::exp(sigma * std::sqrt(T / N)) - 1;
}

BinomialDirectionsVolatility::BinomialDirectionsVolatility(double _sigma,
                                                           double _T, size_t _N)
    : BinomialDirections_new(convertToU(_sigma, _T, _N)),
      sigma(_sigma),
      T(_T),
      periods(_N) {}

double BinomialDirectionsVolatility::getSigma() const { return sigma; }
double BinomialDirectionsVolatility::getT() const { return T; }
size_t BinomialDirectionsVolatility::getPeriods() const { return periods; }

RiskFreeRate::RiskFreeRate(double _spot) : spot(_spot) {}
RiskFreeRateFlat::RiskFreeRateFlat(double _spot) : RiskFreeRate(_spot) {}
double RiskFreeRateFlat::operator()(size_t, size_t) const { return spot(); }

double convertToR(const RiskFreeRateFlat &rfr,
                  const BinomialParametersVolGrid &binomial_params) {
    double r = rfr(0, 0);

    double dt = binomial_params.getDeltaT();
    return std::exp(r * dt) - 1;
}

BinomialDynamic::BinomialDynamic(size_t _N) : N(_N), lattice(N) {}

double BinomialDynamic::getRiskNeutralProbability() const {
    return riskNeutralProbability;
}

size_t BinomialDynamic::getN() const { return N; }

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

BinomialLattice<double> BinomialDynamic::getLattice() const { return lattice; }

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

Option::Option(size_t _N) : N(_N) {}
size_t Option::getN() const { return N; }

EurOption::EurOption(size_t newN) : Option(newN) {}

double EurOption::priceByCRR(BinomialDynamic &modelDynamic) const {
    double q = modelDynamic.getRiskNeutralProbability();
    size_t N = getN();
    assert(N <= modelDynamic.getN());

    modelDynamic.buildLattice();
    BinomialLattice<double> lattice = modelDynamic.getLattice();

    std::vector<double> prices(N + 1);
    for (size_t i = 0; i <= N; ++i) {
        prices[i] = payoff(lattice[N][i]);
    }

    for (int n = N - 1; n >= 0; --n) {
        for (size_t i = 0; i <= n; ++i) {
            double rfr_n_i = modelDynamic.getRFR(n, i);
            double discount_n_i = 1. / (1. + rfr_n_i);

            prices[i] =
                discount_n_i * (q * prices[i + 1] + (1 - q) * prices[i]);
        }
    }

    return prices[0];
}

AmOption::AmOption(size_t newN) : Option(newN), priceTree(N), stoppingTree(N) {}

double AmOption::PriceBySnell(BinomialDynamic &modelDynamic) {
    double q = modelDynamic.getRiskNeutralProbability();
    size_t N = getN();
    assert(N <= modelDynamic.getN());

    double continuationValue{};

    modelDynamic.buildLattice();
    BinomialLattice<double> lattice = modelDynamic.getLattice();

    for (int i = 0; i <= N; i++) {
        priceTree[N][i] = payoff(lattice[N][i]);
        stoppingTree[N][i] = true;
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double rfr_n_i = modelDynamic.getRFR(n, i);
            double discount_n_i = 1. / (1. + rfr_n_i);

            continuationValue = discount_n_i * (q * priceTree[n + 1][i + 1] +
                                                (1. - q) * priceTree[n + 1][i]);

            priceTree[n][i] = payoff(lattice[n][i]);
            stoppingTree[n][i] = true;

            if (continuationValue > priceTree[n][i]) {
                priceTree[n][i] = continuationValue;
                stoppingTree[n][i] = false;
            } else if (priceTree[n][i] == 0.) {
                stoppingTree[n][i] = false;
            }
        }
    }
    return priceTree[0][0];
}

SingleStrike::SingleStrike(size_t newN, double newK)
    : Option(newN), EurOption(newN), AmOption(newN), K(newK) {}

double SingleStrike::getK() const { return K; }

Call::Call(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

Put::Put(size_t newN, double newK) : Option(newN), SingleStrike(newN, newK) {}

double Call::payoff(double z) const { return std::max(z - getK(), 0.); }

double Put::payoff(double z) const { return std::max(getK() - z, 0.); }

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

}  // namespace new_code
