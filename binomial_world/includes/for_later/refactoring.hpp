#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_HPP
#define BINOMIAL_WORLD_REFACTORING_HPP

#include <cassert>
#include <iostream>
#include <vector>

namespace binomial_values {

template <typename T>
class Value {
   protected:
    T value{};

   public:
    Value(T);
    T operator()() const;
    void operator()(T);
};

template <typename T>
std::ostream &operator<<(std::ostream &, const Value<T> &);

// Definitions

template <typename T>
std::ostream &operator<<(std::ostream &os, const Value<T> &myValue) {
    os << myValue();
    return os;
}

template <typename T>
Value<T>::Value(T newValue) : value(newValue) {}

template <typename T>
T Value<T>::operator()() const {
    return value;
}

template <typename T>
void Value<T>::operator()(T newValue) {
    value = newValue;
}

class IntegerValue : public Value<size_t> {
   public:
    IntegerValue(size_t);
};

class RealValue : public Value<double> {
   public:
    RealValue(double);
};

class PositiveInteger : public IntegerValue {
   public:
    PositiveInteger(size_t);
};

class PositiveReal : public RealValue {
   public:
    PositiveReal(double);
};

class NegativeReal : public RealValue {
   public:
    NegativeReal(double);
};

class Volatility : public PositiveReal {
   public:
    Volatility(double);
};

class StockSpot : public PositiveReal {
   public:
    StockSpot(double);
};

class RateSpot : public RealValue {
   public:
    RateSpot(double);
};

class UpFactor : public PositiveReal {
   public:
    UpFactor(double);
};

class DownFactor : public NegativeReal {
   public:
    DownFactor(double);
};

class Periods : public PositiveInteger {
   public:
    Periods(size_t);
};

class TimeToMaturity : public PositiveReal {
   public:
    TimeToMaturity(double);
};

class Size : public IntegerValue {
   public:
    Size(size_t);
};

class MaturityInPeriods : public PositiveInteger {
   public:
    MaturityInPeriods(size_t);
};

class DividendYield : public PositiveReal {
   public:
    DividendYield(double);
};

class ShortRateSpot : public RealValue {
   public:
    ShortRateSpot(double);
};

class Probability : public RealValue {
   public:
    Probability(double);
};

class Strike : public PositiveReal {
   public:
    Strike(double);
};

}  // namespace binomial_values

namespace binomial_lattice {
using namespace binomial_values;

template <typename T>
class BinomialLattice {
   private:
    Size N;
    std::vector<std::vector<T>> lattice;

   public:
    BinomialLattice(size_t);
    size_t size() const;

    const std::vector<T> &operator[](size_t) const;
    std::vector<T> &operator[](size_t);
};

template <typename T>
std::ostream &operator<<(std::ostream &, const std::vector<T> &);

template <typename T>
std::ostream &operator<<(std::ostream &, const BinomialLattice<T> &);

template <typename T>
BinomialLattice<T>::BinomialLattice(size_t newN) : N(newN) {
    lattice.resize(N() + 1);
    for (size_t i = 0; i < N() + 1; i++) {
        lattice[i].resize(i + 1);
    }
}

template <typename T>
const std::vector<T> &BinomialLattice<T>::operator[](size_t i) const {
    assert(i <= N());
    return lattice[i];
}

template <typename T>
std::vector<T> &BinomialLattice<T>::operator[](size_t i) {
    assert(i <= N());
    return lattice[i];
}

template <typename T>
size_t BinomialLattice<T>::size() const {
    return N();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinomialLattice<T> &Lattice) {
    for (size_t i = 0; i <= Lattice.size(); i++) {
        os << Lattice[i] << "\n";
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        os << vector[i] << " ";
    }
    return os;
}

class BinomialLatticeNumeric : public BinomialLattice<double> {
   public:
    BinomialLatticeNumeric(size_t);
};

class BinomialLatticeBoolean : public BinomialLattice<bool> {
   public:
    BinomialLatticeBoolean(size_t);
};

}  // namespace binomial_lattice

namespace binomial_parameters {

using namespace binomial_values;

double getDownFactor(double);
DownFactor getDownFactor(const UpFactor &);

class BinomialParameters {
   public:
    virtual ~BinomialParameters() = default;
    virtual double getU() const = 0;
    virtual double getD() const = 0;
};

class BinomialParametersNoVol : public binomial_parameters::BinomialParameters {
   private:
    UpFactor U;
    DownFactor D;

   public:
    BinomialParametersNoVol(double);

    BinomialParametersNoVol(double, double);

    double getU() const override;
    double getD() const override;
};

class BinomialParametersVolGrid
    : public binomial_parameters::BinomialParameters {
   private:
    Volatility sigma;
    TimeToMaturity T;
    Size N;

   public:
    BinomialParametersVolGrid(double, double, size_t);

    double getSigma() const;
    double getT() const;
    size_t getN() const;

    double getDeltaT() const;

    double getU() const override;
    double getD() const override;
};
}  // namespace binomial_parameters

namespace binomial_model {

using namespace binomial_parameters;

class BinomialModel {
   private:
    UpFactor U;
    DownFactor D;

   public:
    BinomialModel(double, double);
    BinomialModel(const binomial_parameters::BinomialParameters &);

    double getU() const;
    double getD() const;
};

}  // namespace binomial_model

namespace binomial_equities {

using namespace binomial_values;

class Stock {
   private:
    StockSpot spot;
    DividendYield div_yield;

   public:
    Stock(double, double = 0.);

    double getDivYield() const;
    double getSpot() const;
    void setDivYield(double);
    void setSpot(double);
};
}  // namespace binomial_equities

namespace binomial_interest_rates {

using namespace binomial_values;

class ShortRate {
   protected:
    ShortRateSpot spot;

   public:
    ShortRate(double);
    double getSpot() const;
    void setSpot(double);
};
}  // namespace binomial_interest_rates

namespace binomial_dynamic {

using namespace binomial_values;
using namespace binomial_lattice;
using namespace binomial_parameters;
using namespace binomial_model;
using namespace binomial_equities;
using namespace binomial_interest_rates;

class BinomialDynamic {
   protected:
    Size N;
    Probability riskNeutralProbability;
    BinomialLatticeNumeric lattice;
    bool lattice_built = false;

   public:
    BinomialDynamic();
    BinomialDynamic(size_t);
    virtual double getRFR(size_t, size_t) const = 0;
    virtual void buildLattice() = 0;
    double getRiskNeutralProbability() const;
    size_t getN() const;
    const BinomialLatticeNumeric &getLattice() const;
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
    binomial_equities::Stock stock;
    binomial_dynamic::RiskFreeRateFlat riskFreeRateFlat;
    BinomialModel model;

   public:
    StockDynamic(size_t, const binomial_equities::Stock &,
                 const binomial_dynamic::RiskFreeRateFlat &,
                 const binomial_parameters::BinomialParametersNoVol &);

    StockDynamic(size_t, const binomial_equities::Stock &,
                 const binomial_dynamic::RiskFreeRateFlat &,
                 const binomial_parameters::BinomialParametersVolGrid &);

    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
};

}  // namespace binomial_dynamic

namespace binomial_options {

using namespace binomial_values;
using namespace binomial_lattice;
using namespace binomial_dynamic;

class Option {
   protected:
    MaturityInPeriods maturity;

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
    BinomialLatticeNumeric priceTree;
    BinomialLatticeBoolean stoppingTree;

   public:
    AmOption(size_t);
    double priceBySnell(BinomialDynamic &);
    const BinomialLatticeNumeric &getPriceTree() const { return priceTree; }
    const BinomialLatticeBoolean &getStopping() const { return stoppingTree; }
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

}  // namespace binomial_options

namespace binomial_dynamic {

class FuturesDynamic : public BinomialDynamic {
   private:
    MaturityInPeriods maturity;
    BinomialDynamic &primaryAsset;

   public:
    FuturesDynamic(size_t, BinomialDynamic &);
    double getRFR(size_t, size_t) const override;
    void buildLattice() override;
    double price() const;
};
}  // namespace binomial_dynamic

#endif  // BINOMIAL_WORLD_REFACTORING_HPP