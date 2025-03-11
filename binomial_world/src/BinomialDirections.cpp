#include "BinomialDirections.hpp"
#include <cassert>

BinomialDirections::BinomialDirections(double newU)
{
    assert(-1. < newU && newU < 1.);
    U = newU;
    D = -U / (1. + U);
}