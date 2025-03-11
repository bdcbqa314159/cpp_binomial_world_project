#include "Spot.hpp"
#include <cassert>

Spot::Spot(double newValue)
{
    assert(newValue > 0.);
    value = newValue;
}

double Spot::operator()() const
{
    return value;
}