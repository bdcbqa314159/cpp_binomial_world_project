#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_HPP
#define BINOMIAL_WORLD_REFACTORING_HPP

#include "BinomialDirections.hpp"
#include "BinomialLattice.hpp"
#include "Equities.hpp"
#include "Spot.hpp"

namespace new_code {

class RiskFreeRate {
   protected:
    Spot spot;

   public:
    RiskFreeRate(double);
    virtual ~RiskFreeRate() = default;
    virtual double operator()(size_t, size_t) const = 0;
};

class RiskFreeRateFlat : public RiskFreeRate {
   public:
    RiskFreeRateFlat(double);
    double operator()(size_t, size_t) const override;
};

class BinomialDynamic {
   protected:
    size_t N{};
    double riskNeutralProbability{};
    BinomialLattice<double> lattice;
    bool lattice_built = false;

   public:
    BinomialDynamic(size_t);
    virtual double getRFR(size_t, size_t) const = 0;
    virtual void buildLattice() = 0;
    double getRiskNeutralProbability() const;
    size_t getN() const;
};

class StockDynamic : public BinomialDynamic {
   private:
    Stock stock;
    RiskFreeRateFlat riskFreeRateFlat;
    BinomialDirections model;

   public:
    StockDynamic(const Stock &, const RiskFreeRateFlat &,
                 const BinomialDirections &);

    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
    double getRiskNeutralProbability() const;
    size_t getN() const;
};

}  // namespace new_code

#endif  // BINOMIAL_WORLD_REFACTORING_HPP