#pragma once
#ifndef BINOMIAL_WORLD_RISK_FREE_RATE_TERM_STRUCTURE_HPP
#define BINOMIAL_WORLD_RISK_FREE_RATE_TERM_STRUCTURE_HPP

#include "BinomialDynamic.hpp"
#include "InterestRates.hpp"

class RiskFreeRateTermStructure : public RiskFreeRate, public BinomialDynamic {
   private:
    MyBinomialModel model;

   public:
    RiskFreeRateTermStructure(double, size_t, const BinomialParametersNoVol &);
    double operator()(size_t, size_t) const override;
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
};

#endif  // BINOMIAL_WORLD_RISK_FREE_RATE_TERM_STRUCTURE_HPP