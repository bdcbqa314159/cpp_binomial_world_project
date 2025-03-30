#include "ElementaryPrices.hpp"

ElementaryPrices::ElementaryPrices(double new_q, size_t new_N) : q(new_q), N(new_N)
{
    z = BinomialLattice<double>(N + 1);
    zcb.resize(N + 2);
    spotRates.resize(N + 2);
}

void ElementaryPrices::buildLattice(const BinomialLattice<double> &shortRates)
{
    z(0, 0, 1.);
    for (size_t i = 1; i < N + 2; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            if (j == 0)
            {
                z(i, j, z(i - 1, j) * q * 1. / (1. + shortRates(i - 1, j) / 100.));
            }
            else if (j == i)
            {
                z(i, j, z(i - 1, j - 1) * (1. - q) * 1. / (1. + shortRates(i - 1, j - 1) / 100.));
            }

            else
            {
                z(i, j, z(i - 1, j - 1) * (1. - q) * 1. / (1. + shortRates(i - 1, j - 1) / 100.) + z(i - 1, j) * q * 1. / (1. + shortRates(i - 1, j) / 100.));
            }
        }
    }
    latticeBuilt = true;
}

const BinomialLattice<double> &ElementaryPrices::getLattice() const
{
    assert(latticeBuilt);
    return z;
}

void ElementaryPrices::buildRates(const BinomialLattice<double> &shortRates)
{
    zcb[0] = 1.;
    for (size_t i = 1; i < N + 2; i++)
    {
        zcb[i] = 0.;
        for (size_t j = 0; j < i + 1; j++)
            zcb[i] += z(i, j);
    }

    spotRates[0] = 1.;
    for (size_t i = 1; i < N + 2; i++)
    {
        double a = 1. / zcb[i];
        double b = 1. / i;

        spotRates[i] = 100. * (pow(a, b) - 1.);
    }

    ratesBuilt = true;
}

const std::vector<double> &ElementaryPrices::getZCB() const
{
    assert(ratesBuilt);
    return zcb;
}
const std::vector<double> &ElementaryPrices::getSpotRates() const
{
    assert(ratesBuilt);
    return spotRates;
}
