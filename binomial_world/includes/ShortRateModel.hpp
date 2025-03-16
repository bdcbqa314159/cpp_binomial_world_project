#pragma once
#include "BinomialLattice.hpp"

class ShortRateModel {
    // At the moment we rely only on BDT with constant volatility

   private:
    size_t N{};
    BinomialLattice<double> r;
    std::vector<double> a_i;
    double b{};
    bool latticeBuilt{false};

   public:
    ShortRateModel() = default;
    ShortRateModel(const std::vector<double> &, double);
    size_t getN() const;
    void buildLattice();
    const BinomialLattice<double> &getLattice() const;
};