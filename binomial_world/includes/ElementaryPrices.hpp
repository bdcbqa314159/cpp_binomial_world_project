#pragma once
#include <iostream>
#include <vector>
#include "BinomialLattice.hpp"

class ElementaryPrices
{
private:
    double q{};
    size_t N{};
    BinomialLattice<double> z;
    std::vector<double> zcb, spotRates;
    bool latticeBuilt{false}, ratesBuilt{false};

public:
    ElementaryPrices() = default;
    ElementaryPrices(double, size_t);

    void buildLattice(const BinomialLattice<double> &);
    const BinomialLattice<double> &getLattice() const;

    void buildRates(const BinomialLattice<double> &);
    const std::vector<double> &getZCB() const;
    const std::vector<double> &getSpotRates() const;
};