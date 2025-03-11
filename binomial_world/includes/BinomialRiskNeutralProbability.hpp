#pragma once
#include "BinomialRiskFreeRate.hpp"

class BinomialRiskNeutralProbability
{
private:
    BinomialRiskFreeRate riskFreeRate;
    double q{}, p{};

public:
    BinomialRiskNeutralProbability(double, double);
    double getQ() const { return q; }
    double getP() const { return p; }
    double getR() const { return riskFreeRate.getR(); }
    double getU() const { return riskFreeRate.getU(); }
    double getD() const { return riskFreeRate.getD(); }
};