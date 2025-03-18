#pragma once
#include "BinomialLattice.hpp"

class BinomialModel {
   protected:
    size_t N{};
    BinomialLattice<double> lattice;
    bool lattice_built = false;
    double riskNeutralProbability{};
    double riskFreeRate{};

   public:
    BinomialModel(size_t);
    virtual void buildLattice() = 0;
    double getRiskNeutralProbability() const;
    double getRiskFreeRate() const;
    size_t getN() const;
    const BinomialLattice<double> &getLattice() const;
};