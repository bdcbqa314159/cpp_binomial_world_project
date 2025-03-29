#pragma once
#ifndef BINOMIAL_WORLD_VOLGRIDADAPTER_HPP
#define BINOMIAL_WORLD_VOLGRIDADAPTER_HPP

#include "BinomialDirections.hpp"
#include "BinomialVolGrid.hpp"

class VolGridAdapter : public BinomialDirections {
   private:
    BinomialVolGrid volGrid;

   public:
    VolGridAdapter(const BinomialVolGrid &);
    double getSigma() const;
    double getTimeToMaturity() const;
    size_t getPeriods() const;

    double getDeltaT() const;
};

#endif  // BINOMIAL_WORLD_VOLGRIDADAPTER_HPP