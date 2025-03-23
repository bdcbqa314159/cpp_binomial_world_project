#pragma once
#ifndef BINOMIAL_WORLD_ZERO_COUPON_BOND_DYNAMIC_HPP
#define BINOMIAL_WORLD_ZERO_COUPON_BOND_DYNAMIC_HPP

#include "RiskFreeRateTermStructure.hpp"

class ZeroCouponBondDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    RiskFreeRateTermStructure &primaryAsset;
    double faceValue = 1.;

   public:
    ZeroCouponBondDynamic(size_t, RiskFreeRateTermStructure &, double = 1.);
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

#endif  // BINOMIAL_WORLD_ZERO_COUPON_BOND_DYNAMIC_HPP