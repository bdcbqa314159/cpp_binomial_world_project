#include "BinomialRiskFreeRate.hpp"
#include <cassert>

BinomialRiskFreeRate::BinomialRiskFreeRate(double newU, double newR) : directions(newU)
{
    assert(directions.getD() < newR && newR < directions.getU());
    R = newR;
}
