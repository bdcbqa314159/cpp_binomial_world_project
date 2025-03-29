#include "InterestRates.hpp"

ShortRate::ShortRate(double newSpot) : spot(newSpot) {}

double ShortRate::getSpot() const { return spot(); }
void ShortRate::setSpot(double newSpot) { spot(newSpot); }