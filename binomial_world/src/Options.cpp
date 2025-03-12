#include "Options.hpp"
#include <cassert>

Option::Option(size_t newN) : N(newN) {}

EurOption::EurOption(size_t newN) : Option(newN) {}

double EurOption::priceByCRR(const BinomialModel &model) const
{
    double q = model.riskNeutralProbability();
    size_t N = getN();

    double discount = 1. / (1. + model.getR());
    BinomialLattice<double> lattice = model.getLattice();

    std::vector<double> prices(N + 1);
    for (size_t i = 0; i <= N; ++i)
    {
        prices[i] = payoff(lattice(N, i));
    }

    for (int n = N - 1; n >= 0; --n)
    {
        for (size_t i = 0; i <= n; ++i)
        {
            prices[i] = discount * (q * prices[i + 1] + (1 - q) * prices[i]);
        }
    }

    return prices[0];
}

AmOption::AmOption(size_t newN) : Option(newN) {}

double AmOption::PriceBySnell(const BinomialModel &model) const
{
    double q = model.riskNeutralProbability();
    size_t N = getN();

    BinomialLattice<double> priceTree(N);
    BinomialLattice<bool> stoppingTree(N);
    double continuationValue{};
    double discount = 1. / (1 + model.getR());

    for (int i = 0; i <= N; i++)
    {
        priceTree(N, i, payoff(model(N, i)));
        stoppingTree(N, i, true);
    }

    for (int n = N - 1; n >= 0; --n)
    {
        for (int i = 0; i <= n; ++i)
        {
            continuationValue = discount * (q * priceTree(n + 1, i + 1) + (1. - q) * priceTree(n + 1, i));
            priceTree(n, i, payoff(model(n, i)));
            stoppingTree(n, i, true);

            if (continuationValue > priceTree(n, i))
            {
                priceTree(n, i, continuationValue);
                stoppingTree(n, i, false);
            }
            else if (priceTree(n, i) == 0.)
            {
                stoppingTree(n, i, false);
            }
        }
    }
    return priceTree(0, 0);
}
