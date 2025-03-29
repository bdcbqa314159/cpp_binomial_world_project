#pragma once
#ifndef BINOMIAL_WORLD_INTERESTRATES_HPP
#define BINOMIAL_WORLD_INTERESTRATES_HPP

#include "Numeric.hpp"

class ShortRate {
   private:
    Spot spot;

   public:
    ShortRate(double);
    double getSpot() const;
    void setSpot(double);
};

#endif  // BINOMIAL_WORLD_INTERESTRATES_HPP