#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_HPP
#define BINOMIAL_WORLD_REFACTORING_HPP

#include "BinomialDirections.hpp"
#include "BinomialLattice.hpp"
#include "Equities.hpp"
#include "Spot.hpp"

namespace new_code {

class BinomialDirections_new {
   private:
    double U{}, D{};

   public:
    BinomialDirections_new(double _U);
    BinomialDirections_new(double _U, double _D);
    double getU() const;
    double getD() const;
};

class BinomialDirectionsVolatility : public BinomialDirections_new {
   private:
    double sigma{}, T{};
    size_t periods{};

   public:
    BinomialDirectionsVolatility(double, double, size_t);
    double getSigma() const;
    double getT() const;
    size_t getPeriods() const;
};

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
    BinomialLattice<double> getLattice() const;
};

class StockDynamic : public BinomialDynamic {
   private:
    Stock stock;
    RiskFreeRateFlat riskFreeRateFlat;
    BinomialDirections_new model;

   public:
    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const BinomialDirections_new &);
    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const BinomialDirectionsVolatility &);

    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
    double getRiskNeutralProbability() const;
    size_t getN() const;
};

class Option {
   protected:
    size_t N{};

   public:
    Option(size_t);
    virtual ~Option() = default;
    size_t getN() const;
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
    double PriceBySnell(BinomialDynamic &);
    const BinomialLattice<double> &getPriceTree() const { return priceTree; }
    const BinomialLattice<bool> &getStopping() const { return stoppingTree; }
};

class SingleStrike : public EurOption, public AmOption {
   protected:
    double K{};

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

}  // namespace new_code

#endif  // BINOMIAL_WORLD_REFACTORING_HPP