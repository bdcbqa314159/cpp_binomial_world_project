#include "Options.hpp"

Option::Option(size_t newMaturity) : maturity(newMaturity) {}
size_t Option::getMaturity() const { return maturity; }

EurOption::EurOption(size_t newMaturity) : Option(newMaturity) {}

double EurOption::priceByCRR(BinomialDynamic &modelDynamic) const {
    double q = modelDynamic.getRiskNeutralProbability();
    assert(maturity <= modelDynamic.getPeriods());
    BinomialLattice<double> lattice = modelDynamic.getLattice();

    size_t N = maturity;

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

AmOption::AmOption(size_t newMaturity)
    : Option(newMaturity), priceTree(newMaturity), stoppingTree(newMaturity) {}

double AmOption::priceBySnell(BinomialDynamic &modelDynamic) {
    double q = modelDynamic.getRiskNeutralProbability();

    assert(maturity <= modelDynamic.getPeriods());

    double continuationValue{};

    BinomialLattice<double> lattice = modelDynamic.getLattice();

    size_t N = maturity;

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