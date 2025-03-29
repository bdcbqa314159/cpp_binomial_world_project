#pragma once
#ifndef EQUITIES_HPP
#define EQUITIES_HPP

#include "Numeric.hpp"

class Stock {
   private:
    Spot spot;
    DividendYield div_yield;

   public:
    Stock(double, double = 0.);
    double getDivYield() const;
    double getSpot() const;
    void setDivYield(double);
    void setSpot(double);
};

#endif  // EQUITIES_HPP