#include "refactoring_10.hpp"

#include "refactoring_1.hpp"
#include "refactoring_5.hpp"
#include "refactoring_7.hpp"

namespace new_code {
AmOption::AmOption(size_t newN) : Option(newN), priceTree(N), stoppingTree(N) {}

double AmOption::PriceBySnell(const BinomialModelDynamic &modelDynamic) {
    double q = modelDynamic.getRiskNeutralProbability();
    size_t N = getN();

    double continuationValue{};
    double discount = 1. / (1 + modelDynamic.getRiskFreeRate());

    BinomialModelLatticeBuilder myBuilder(modelDynamic);
    BinomialLattice<double> lattice = myBuilder.getLattice();

    for (int i = 0; i <= N; i++) {
        priceTree(N, i, payoff(lattice(N, i)));
        stoppingTree(N, i, true);
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            continuationValue = discount * (q * priceTree(n + 1, i + 1) +
                                            (1. - q) * priceTree(n + 1, i));
            priceTree(n, i, payoff(lattice(n, i)));
            stoppingTree(n, i, true);

            if (continuationValue > priceTree(n, i)) {
                priceTree(n, i, continuationValue);
                stoppingTree(n, i, false);
            } else if (priceTree(n, i) == 0.) {
                stoppingTree(n, i, false);
            }
        }
    }
    return priceTree(0, 0);
}
}  // namespace new_code