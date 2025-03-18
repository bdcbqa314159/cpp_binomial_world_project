#include "Equities.hpp"

#include <cassert>

Stock::Stock(double _spot, double _div_yield)
    : spot(_spot), div_yield(_div_yield) {
    assert(spot > 0.);
    assert(0. <= div_yield && div_yield < 1.);
}

double Stock::getDivYield() const { return div_yield; }
void Stock::setDivYield(double _div_yield) {
    assert(0. <= div_yield && div_yield < 1.);
    div_yield = _div_yield;
}

void Stock::setSpot(double _spot) {
    assert(spot > 0.);
    spot = _spot;
}