#pragma once
#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include "BinomialDynamic.hpp"
#include "BinomialLattice.hpp"

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

// Prototype for in arrears options must work with design patterns later

class OptionInArrears {
   protected:
    size_t maturity;

   public:
    OptionInArrears(size_t);
    virtual ~OptionInArrears() = default;
    size_t getMaturity() const;
    virtual double payoff(double) const = 0;
};

class EurOptInArrears : public virtual OptionInArrears {
   public:
    EurOptInArrears(size_t);

    double priceByCRR(BinomialDynamic &) const;
};

#endif  // OPTIONS_HPP