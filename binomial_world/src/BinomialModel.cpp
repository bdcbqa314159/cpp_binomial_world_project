#include "BinomialModel.hpp"
#include <cassert>

BinomialModel::BinomialModel(double newS0, double newU, double newR, size_t newN) : S0(newS0), q(newU, newR), N(newN), lattice(N)
{
    buildLattice();
    built = true;
}

double BinomialModel::getR() const
{
    return q.getR();
}

double BinomialModel::riskNeutralProbability() const
{
    return q.getQ();
}

void BinomialModel::buildLattice()
{
    double U = q.getU();
    double D = q.getD();

    lattice(0, 0) = S0();

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            if (j == 0)
                lattice(i, j) = lattice(i - 1, j) * (1. + D);
            else if (j == i)
                lattice(i, j) = lattice(i - 1, j - 1) * (1. + U);
            else
                lattice(i, j) = lattice(i - 1, j - 1) * (1. + U);
        }
    }
}

const BinomialLattice<double> &BinomialModel::getLattice() const
{
    assert(built);
    return lattice;
}

const double &BinomialModel::operator()(size_t i, size_t j) const
{
    return lattice(i, j);
}

size_t BinomialModel::getN() const
{
    return N;
}

BinomialLattice<double> &BinomialModel::changeLattice()
{
    assert(built);
    return lattice;
}