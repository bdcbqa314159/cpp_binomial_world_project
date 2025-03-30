#pragma once
#ifndef BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP
#define BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP

#include "BinomialDirections.hpp"
#include "BinomialLattice.hpp"
#include "CouponPayment.hpp"
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
    virtual double getCouponPayment(size_t, size_t) const = 0;
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
    double getCouponPayment(size_t, size_t) const override;
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
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
};

class FuturesDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    BinomialDynamic &primaryAsset;

   public:
    FuturesDynamic(size_t, BinomialDynamic &);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

class RiskFreeRateTerm : public BinomialDynamic {
   private:
    ShortRate shortRate;
    BinomialDirections model;

   public:
    RiskFreeRateTerm(size_t, const ShortRate &, const BinomialDirections &);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
};

class ZeroCouponBondDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    RiskFreeRateTerm &primaryAsset;
    double faceValue = 1.;

   public:
    ZeroCouponBondDynamic(size_t, RiskFreeRateTerm &, double = 1.);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

class CouponBearingBondDynamic : public BinomialDynamic {
   private:
    size_t maturity = 0;
    RiskFreeRateTerm primaryAsset;
    CouponPayment couponPayment;
    double faceValue = 1.;

   public:
    CouponBearingBondDynamic(size_t, RiskFreeRateTerm &, double, double,
                             size_t = 1);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

class ForwardsDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    BinomialDynamic &primaryAsset;

   public:
    ForwardsDynamic(size_t, BinomialDynamic &);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

class SwapDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    BinomialDynamic &primaryAsset;
    double fixedRate{};

   public:
    SwapDynamic(size_t, BinomialDynamic &, double);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

class ElementaryPrices : public BinomialDynamic {
   private:
    size_t maturity = 0;
    RiskFreeRateTerm primaryAsset;
    std::vector<double> zcb, spotRates;

   public:
    ElementaryPrices(RiskFreeRateTerm &);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
    void buildRates();

    const std::vector<double> &getZCB() const;
    const std::vector<double> &getSpotRates() const;
};

// New kind of design for future refactoring ... yes again XD

class BinomialModelParameters {
   public:
    virtual void buildLattice(BinomialLattice<double> &) = 0;
    virtual std::unique_ptr<BinomialModelParameters> clone() const = 0;
    virtual ~BinomialModelParameters() = default;
};

class BDTParameters : public BinomialModelParameters {
   private:
    std::vector<double> a_i;
    double b{};

   public:
    std::unique_ptr<BinomialModelParameters> clone() const override;

    BDTParameters(const std::vector<double> &, double);

    void buildLattice(BinomialLattice<double> &lattice) override;

    const std::vector<double> &getSpotRates() const;
    double getB() const;
};

class RiskFreeRateTermModel : public BinomialDynamic {
   private:
    ShortRate shortRate;
    std::unique_ptr<BinomialModelParameters> model;

   public:
    RiskFreeRateTermModel(size_t, const ShortRate &,
                          const BinomialModelParameters &);
    double getRFR(size_t, size_t) const override;
    double getCouponPayment(size_t, size_t) const override;
    void buildLattice() override;
};

#endif  // BINOMIAL_WORLD_BINOMIALDYNAMIC_HPP