#include "Futures.hpp"

void Futures::setValue(size_t i, size_t j, double x)
{
    changeLattice()(i, j, x);
}

double Futures::getValue(size_t i, size_t j) const
{
    return getLattice()(i, j);
}

Futures::Futures(double newS0, double newU, double newR, size_t newN) : BinomialModel(newS0, newU, newR, newN) {}

double Futures::price()
{
    double q = riskNeutralProbability();
    double R = getR();
    size_t N = getN();

    for (int n = N - 1; n >= 0; --n)
    {
        for (int i = 0; i <= n; ++i)
        {
            setValue(n, i, q * getValue(n + 1, i + 1) + (1. - q) * getValue(n + 1, i));
        }
    }

    return getValue(0, 0);
};