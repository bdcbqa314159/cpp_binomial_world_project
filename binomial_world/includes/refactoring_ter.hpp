#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_TER_HPP
#define BINOMIAL_WORLD_REFACTORING_TER_HPP

#include <cassert>
#include <iostream>
#include <vector>

namespace new_code_bis {

template <typename T>
class BinomialLattice {
   private:
    size_t periods{};
    std::vector<std::vector<T>> lattice;

   public:
    BinomialLattice(size_t);
    size_t getPeriods() const;
    const std::vector<std::vector<T>> &getLattice() const;

    const std::vector<T> &operator[](size_t) const;
    std::vector<T> &operator[](size_t);
};

template <typename T>
BinomialLattice<T>::BinomialLattice(size_t newPeriods) : periods(newPeriods) {
    lattice.resize(periods + 1);
    for (size_t i = 0; i <= periods; i++) {
        lattice[i].resize(i + 1);
    }
}

template <typename T>
const std::vector<T> &BinomialLattice<T>::operator[](size_t i) const {
    assert(i <= periods);
    return lattice[i];
}

template <typename T>
std::vector<T> &BinomialLattice<T>::operator[](size_t i) {
    assert(i <= periods);
    return lattice[i];
}

template <typename T>
size_t BinomialLattice<T>::getPeriods() const {
    return periods;
}

template <typename T>
const std::vector<std::vector<T>> &BinomialLattice<T>::getLattice() const {
    return lattice;
}

template <typename T>
std::ostream &operator<<(std::ostream &, const std::vector<T> &);

template <typename T>
std::ostream &operator<<(std::ostream &, const BinomialLattice<T> &);

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    for (const T &element : vector) {
        os << element << " ";
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinomialLattice<T> &Lattice) {
    for (const std::vector<T> &row : Lattice.getLattice()) {
        os << row << "\n";
    }
    return os;
}

class BinomialDirections {
   private:
    double u{}, d{};

   public:
    BinomialDirections(double);
    BinomialDirections(double, double);

    double getU() const;
    double getD() const;

    void setDirections(double, double);
};

void latticeBuilder(double, double, double, size_t, BinomialLattice<double> &);

class Numeric {
   protected:
    double value{};

   public:
    Numeric(double);
    double operator()() const;
    void operator()(double);
};

class Spot : public Numeric {
   public:
    Spot(double);
};

class DividendYield : public Numeric {
   public:
    DividendYield(double);
};

class Probability : public Numeric {
   public:
    Probability(double);
};

class Stock {
   private:
    Spot spot;
    DividendYield div_yield;

   public:
    Stock(double, double = 0.);
    double getDivYield() const;
    double getSpot() const;
    void setDivYield(double);
    void setSpot(double);
};

class ShortRate {
   private:
    Spot spot;

   public:
    ShortRate(double);
    double getSpot() const;
    void setSpot(double);
};

class BinomialDynamic {
   protected:
    size_t periods{0};
    Probability riskNeutralProbability{1.};
    BinomialLattice<double> lattice{1};
    bool lattice_built = false;

   public:
    BinomialDynamic() = default;
    BinomialDynamic(size_t);
    virtual double getRFR(size_t, size_t) const = 0;
    virtual void buildLattice() = 0;
    double getRiskNeutralProbability() const;
    size_t getPeriods() const;
    const BinomialLattice<double> &getLattice() const;
};

class RiskFreeRateFlat : public BinomialDynamic {
   private:
    ShortRate shortRate;

   public:
    RiskFreeRateFlat(double);
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
};

class StockDynamic : public BinomialDynamic {
   private:
    Stock stock;
    RiskFreeRateFlat riskFreeRateFlat;
    BinomialDirections model;

   public:
    StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
                 const BinomialDirections &);

    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
};

class FuturesDynamic : public BinomialDynamic {
   private:
    size_t maturity;
    BinomialDynamic &primaryAsset;

   public:
    FuturesDynamic(size_t, BinomialDynamic &);
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};

class Strike : public Numeric {
   public:
    Strike(double);
};

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