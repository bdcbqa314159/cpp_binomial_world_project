#pragma once
#include "BinomialLattice.hpp"
#include "BinomialRiskNeutralProbability.hpp"
#include "Spot.hpp"

class BinomialModel {
   private:
    Spot S0;
    size_t N{};
    BinomialRiskNeutralProbability q;
    BinomialLattice<double> lattice;
    bool built{false};

    void buildLattice();

   public:
    BinomialModel() = default;
    BinomialModel(double, double, double, size_t);
    size_t getN() const;
    double getR() const;
    double riskNeutralProbability() const;
    const BinomialLattice<double> &getLattice() const;
    BinomialLattice<double> &changeLattice();
    const double &operator()(size_t, size_t) const;
};
