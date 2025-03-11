#pragma once
#include "BinomialDirections.hpp"

class BinomialRiskFreeRate
{
private:
    BinomialDirections directions;
    double R{};

public:
    BinomialRiskFreeRate() = default;
    BinomialRiskFreeRate(double, double);
    double getR() const { return R; }
    double getU() const { return directions.getU(); }
    double getD() const { return directions.getD(); }
    const BinomialDirections &getDirections() const { return directions; }
};