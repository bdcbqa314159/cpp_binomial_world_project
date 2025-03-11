#include "BinomialRiskNeutralProbability.hpp"

BinomialRiskNeutralProbability::BinomialRiskNeutralProbability(double newU, double newR) : riskFreeRate(newU, newR)
{
    double U = riskFreeRate.getU();
    double D = riskFreeRate.getD();
    double R = riskFreeRate.getR();
    q = (R - D) / (U - D);
    p = 1. - q;
}
