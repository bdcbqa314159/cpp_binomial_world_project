#include "Equities.hpp"

Stock::Stock(double newSpot, double newDivYield)
    : spot(newSpot), div_yield(newDivYield) {}

double Stock::getDivYield() const { return div_yield(); }
double Stock::getSpot() const { return spot(); }

void Stock::setDivYield(double newDivYield) { div_yield(newDivYield); }

void Stock::setSpot(double newSpot) { spot(newSpot); }