#pragma once
#include "BinomialModel.hpp"

class Option {
   protected:
    size_t N{};

   public:
    // Option() = default;
    Option(size_t);
    virtual ~Option() = default;
    size_t getN() const { return N; }
    virtual double payoff(double) const = 0;
};

class EurOption : public virtual Option {
   public:
    // EurOption() = default;
    EurOption(size_t);

    double priceByCRR(const BinomialModel &) const;
};

class AmOption : public virtual Option {
   private:
    BinomialLattice<double> priceTree;
    BinomialLattice<bool> stoppingTree;

   public:
    // AmOption() = default;
    AmOption(size_t);
    double PriceBySnell(const BinomialModel &);
    const BinomialLattice<double> &getPriceTree() const { return priceTree; }
    const BinomialLattice<bool> &getStopping() const { return stoppingTree; }
};