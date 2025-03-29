#pragma once
#ifndef BINOMIAL_WORLD_UTILS_HPP
#define BINOMIAL_WORLD_UTILS_HPP

#include "BinomialDynamic.hpp"
#include "BinomialLattice.hpp"

void latticeBuilder(double, double, double, size_t, BinomialLattice<double> &);
double zeroCouponBondPrice(const BinomialDynamic &, size_t, double = 1.);

#endif  // BINOMIAL_WORLD_UTILS_HPP