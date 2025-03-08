#include "ShortRateModel.hpp"

ShortRateModel::ShortRateModel(size_t new_N, const std::vector<double> &new_a_i, double new_b) : N(new_N), a_i(new_a_i), b(new_b)
{
    r = BinomialLattice<double>(N);
}

void ShortRateModel::buildLattice()
{
    double r0 = a_i[0];
    r(0, 0, r0);
    for (size_t i = 1; i < N + 1; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            r(i, j, a_i[i] * exp(b * j));
        }
    }
    latticeBuilt = true;
}

const BinomialLattice<double> &ShortRateModel::getLattice() const
{
    return r;
}