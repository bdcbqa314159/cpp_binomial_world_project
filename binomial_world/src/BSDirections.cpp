#include "BSDirections.hpp"

#include <cassert>
#include <cmath>

BSDirections::BSDirections(double _r) : r(_r) { assert(r > 0.); }

BSDirections::BSDirections(double _r, double _sigma, double _T, size_t _N)
    : r(_r), sigma(_sigma), T(_T), N(_N) {
    assert(r > 0.);
    assert(sigma > 0.);
    assert(T > 0.);
    assert(N > 0);
    no_diffusion = false;
}

double BSDirections::getR() const { return r; }
double BSDirections::getSigma() const { return sigma; }
double BSDirections::getT() const { return T; }
size_t BSDirections::getN() const { return N; }
bool BSDirections::onlyDrift() const { return no_diffusion; }
double BSDirections::getU() const {
    assert(!no_diffusion);

    double dt = T / N;
    return std::exp(sigma * std::sqrt(dt)) - 1.;
}