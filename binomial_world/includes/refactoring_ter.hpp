#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_TER_HPP
#define BINOMIAL_WORLD_REFACTORING_TER_HPP

#include <iostream>
#include <vector>

#include "BinomialDirections.hpp"
#include "BinomialDynamic.hpp"
#include "BinomialLattice.hpp"
#include "BinomialVolGrid.hpp"
#include "Common.hpp"
#include "Equities.hpp"
#include "InterestRates.hpp"
#include "Numeric.hpp"
#include "Options.hpp"
#include "Utils.hpp"
#include "VolGridAdapter.hpp"

namespace new_code_bis {

class SingleStrike : public EurOption, public AmOption {
   protected:
    Strike K;

   public:
    SingleStrike(size_t, double);
    double getK() const;
};

class Call : public SingleStrike {
   public:
    Call(size_t, double);
    double payoff(double) const override;
};

class Put : public SingleStrike {
   public:
    Put(size_t, double);
    double payoff(double) const override;
};

}  // namespace new_code_bis

#endif  // BINOMIAL_WORLD_REFACTORING_TER_HPP