#include "refactoring_9.hpp"

#include "refactoring_1.hpp"
#include "refactoring_5.hpp"
#include "refactoring_7.hpp"

namespace new_code {
EurOption::EurOption(size_t newN) : Option(newN) {}

double EurOption::priceByCRR(const BinomialModelDynamic &modelDynamic) const {
    double q = modelDynamic.getRiskNeutralProbability();
    size_t N = getN();

    double discount = 1. / (1. + modelDynamic.getRiskFreeRate());

    BinomialModelLatticeBuilder myBuilder(modelDynamic);
    BinomialLattice<double> lattice = myBuilder.getLattice();

    std::vector<double> prices(N + 1);
    for (size_t i = 0; i <= N; ++i) {
        prices[i] = payoff(lattice(N, i));
    }

    for (int n = N - 1; n >= 0; --n) {
        for (size_t i = 0; i <= n; ++i) {
            prices[i] = discount * (q * prices[i + 1] + (1 - q) * prices[i]);
        }
    }

    return prices[0];
}
}  // namespace new_code