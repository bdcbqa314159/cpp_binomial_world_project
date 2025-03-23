#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_HPP
#define BINOMIAL_WORLD_REFACTORING_HPP

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

class Size : public PositiveInteger {
   public:
    Size(size_t);
};

class MaturityInPeriods : public PositiveInteger {
   public:
    MaturityInPeriods(size_t);
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

class BinomialParametersNoVol : public BinomialParameters {
   private:
    UpFactor U;
    DownFactor D;

   public:
    BinomialParametersNoVol(double);

    BinomialParametersNoVol(double, double);

    double getU() const override;
    double getD() const override;
};

class BinomialParametersVolGrid : public BinomialParameters {
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

#endif  // BINOMIAL_WORLD_REFACTORING_HPP