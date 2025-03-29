#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_TER_HPP
#define BINOMIAL_WORLD_REFACTORING_TER_HPP

#include <iostream>
#include <vector>

#include "BinomialDirections.hpp"
#include "BinomialLattice.hpp"
#include "BinomialVolGrid.hpp"
#include "Common.hpp"
#include "Equities.hpp"
#include "Numeric.hpp"
#include "Utils.hpp"
#include "VolGridAdapter.hpp"

namespace new_code_bis {

class ShortRate {
   private:
    Spot spot;

   public:
    ShortRate(double);
    double getSpot() const;
    void setSpot(double);
};

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

class Option {
   protected:
    size_t maturity;

   public:
    Option(size_t);
    virtual ~Option() = default;
    size_t getMaturity() const;
    virtual double payoff(double) const = 0;
};

class EurOption : public virtual Option {
   public:
    EurOption(size_t);

    double priceByCRR(BinomialDynamic &) const;
};

class AmOption : public virtual Option {
   private:
    BinomialLattice<double> priceTree;
    BinomialLattice<bool> stoppingTree;

   public:
    AmOption(size_t);
    double priceBySnell(BinomialDynamic &);
    const BinomialLattice<double> &getPriceTree() const { return priceTree; }
    const BinomialLattice<bool> &getStopping() const { return stoppingTree; }
};

class SingleStrike : public EurOption, public AmOption {
   protected:
    Strike K;

   public:
    SingleStrike(size_t, double);
    double getK() const;
};

class Call : public SingleStrike {
   public:
    Call(size_t, double);
    double payoff(double) const override;
};

class Put : public SingleStrike {
   public:
    Put(size_t, double);
    double payoff(double) const override;
};

}  // namespace new_code_bis

#endif  // BINOMIAL_WORLD_REFACTORING_TER_HPP