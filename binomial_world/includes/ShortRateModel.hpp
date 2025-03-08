#pragma once
#include <iostream>
#include "BinomialLattice.hpp"

class ShortRateModel
{
    // At the moment we rely only on BDT with constant volatility

private:
    double q{};
    size_t N{};
    BinomialLattice<double> r;
    std::vector<double> a_i;
    double b{};

public:
    ShortRateModel() = default;
    ShortRateModel(double, size_t, const std::vector<double> &, double);

    void buildLattice();
    const BinomialLattice<double> &getLattice() const;
};