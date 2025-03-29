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
#include "Utils.hpp"
#include "VolGridAdapter.hpp"

namespace new_code_bis {

class Option {
   protected:
    size_t maturity;

   public:
    Option(size_t);
    virtual ~Option() = default;
    size_t getMaturity() const;
    virtual double payoff(double) const = 0;
};

class EurOption : public virtual Option {
   public:
    EurOption(size_t);

    double priceByCRR(BinomialDynamic &) const;
};

class AmOption : public virtual Option {
   private:
    BinomialLattice<double> priceTree;
    BinomialLattice<bool> stoppingTree;

   public:
    AmOption(size_t);
    double priceBySnell(BinomialDynamic &);
    const BinomialLattice<double> &getPriceTree() const { return priceTree; }
    const BinomialLattice<bool> &getStopping() const { return stoppingTree; }
};

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