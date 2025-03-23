#pragma once
#ifndef BINOMIAL_VALUES_HPP
#define BINOMIAL_VALUES_HPP

#include "BinomialValuesTemplate.hpp"

namespace binomial_values {

class IntegerValue : public Value<size_t> {
   public:
    IntegerValue(size_t);
};

class RealValue : public Value<double> {
   public:
    RealValue(double);
};

class PositiveInteger : public IntegerValue {
   public:
    PositiveInteger(size_t);
};

class PositiveReal : public RealValue {
   public:
    PositiveReal(double);
};

class NegativeReal : public RealValue {
   public:
    NegativeReal(double);
};

class Volatility : public PositiveReal {
   public:
    Volatility(double);
};

class StockSpot : public PositiveReal {
   public:
    StockSpot(double);
};

class RateSpot : public RealValue {
   public:
    RateSpot(double);
};

class UpFactor : public PositiveReal {
   public:
    UpFactor(double);
};

class DownFactor : public NegativeReal {
   public:
    DownFactor(double);
};

class Periods : public PositiveInteger {
   public:
    Periods(size_t);
};

class Size : public PositiveInteger {
   public:
    Size(size_t);
};

}  // namespace binomial_values

#endif