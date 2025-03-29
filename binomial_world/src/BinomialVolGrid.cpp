#include "BinomialVolGrid.hpp"

#include <cassert>

BinomialVolGrid::BinomialVolGrid(double newSigma, double newTimeToMaturity,
                                 size_t newPeriods)
    : sigma(newSigma), timeToMaturity(newTimeToMaturity), periods(newPeriods) {
    assert(sigma > 0. && timeToMaturity > 0. && periods > 0);
}

double BinomialVolGrid::getSigma() const { return sigma; }
double BinomialVolGrid::getTimeToMaturity() const { return timeToMaturity; }
size_t BinomialVolGrid::getPeriods() const { return periods; }

double BinomialVolGrid::getDeltaT() const { return timeToMaturity / periods; }