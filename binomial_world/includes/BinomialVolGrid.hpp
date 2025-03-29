#pragma once
#ifndef BINOMIAL_WORLD_BINOMIALVOLGRID_HPP
#define BINOMIAL_WORLD_BINOMIALVOLGRID_HPP

#include <cstddef>

class BinomialVolGrid {
   private:
    double sigma, timeToMaturity;
    size_t periods;

   public:
    BinomialVolGrid(double, double, size_t);

    double getSigma() const;
    double getTimeToMaturity() const;
    size_t getPeriods() const;

    double getDeltaT() const;
};

#endif  // BINOMIAL_WORLD_BINOMIALVOLGRID_HPP