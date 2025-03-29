#pragma once
#ifndef BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP
#define BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP

#include "BinomialDirections.hpp"
#include "BinomialLattice.hpp"
#include "Equities.hpp"
#include "InterestRates.hpp"
#include "Numeric.hpp"
#include "VolGridAdapter.hpp"

class BinomialDynamic {
   protected:
    size_t periods{0};
    Probability riskNeutralProbability{1.};
    BinomialLattice<double> lattice{1};
    bool lattice_built = false;

   public:
    BinomialDynamic() = default;
    BinomialDynamic(size_t);
    virtual double getRFR(size_t, size_t) const = 0;
    virtual void buildLattice() = 0;
    double getRiskNeutralProbability() const;
    size_t getPeriods() const;
    const BinomialLattice<double> &getLattice() const;
};

class RiskFreeRateFlat : public BinomialDynamic {
   private:
    ShortRate shortRate;

   public:
    RiskFreeRateFlat(double);
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
};

class StockDynamic : public BinomialDynamic {
   private:
    Stock stock;
    RiskFreeRateFlat riskFreeRateFlat;
    BinomialDirections model;

   public:
    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const BinomialDirections &);
    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const VolGridAdapter &);

    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
};

class FuturesDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    BinomialDynamic &primaryAsset;

   public:
    FuturesDynamic(size_t, BinomialDynamic &);
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

#endif  // BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP