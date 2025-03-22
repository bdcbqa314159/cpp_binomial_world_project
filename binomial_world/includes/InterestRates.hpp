#pragma once
#ifndef BINOMIAL_WORLD_INTERESTRATES_HPP
#define BINOMIAL_WORLD_INTERESTRATES_HPP

#include "Spot.hpp"

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

#endif  // BINOMIAL_WORLD_INTERESTRATES_HPP