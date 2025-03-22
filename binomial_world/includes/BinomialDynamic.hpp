#pragma once
#ifndef BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP
#define BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP

#include "BinomialLattice.hpp"
#include "BinomialModel.hpp"
#include "Equities.hpp"
#include "InterestRates.hpp"

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
    BinomialLattice<double> getLattice() const;
};

double convertToR(const RiskFreeRateFlat &, const BinomialParametersVolGrid &);

class StockDynamic : public BinomialDynamic {
   private:
    Stock stock;
    RiskFreeRateFlat riskFreeRateFlat;
    MyBinomialModel model;

   public:
    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const BinomialParametersNoVol &);

    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const BinomialParametersVolGrid &);

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