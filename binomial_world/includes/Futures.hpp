#pragma once
#include "BinomialModel.hpp"

class Futures : public BinomialModel {
   public:
    Futures() = default;
    Futures(double, double, double, size_t);

    void setValue(size_t i, size_t j, double x);
    double getValue(size_t i, size_t j) const;

    double price();
};