#include "BinomialDirections.hpp"

#include <cassert>

BinomialDirections::BinomialDirections(double newU) : u(newU) {
    assert(0. < u);
    d = 1 / u;
}

BinomialDirections::BinomialDirections(double newU, double newD)
    : u(newU), d(newD) {
    assert(0. < d && d < u);
}

double BinomialDirections::getU() const { return u; }
double BinomialDirections::getD() const { return d; }

void BinomialDirections::setDirections(double newU, double newD) {
    u = newU;
    d = newD;

    assert(0. < d && d < u);
}