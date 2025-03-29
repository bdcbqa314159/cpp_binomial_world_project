#pragma once
#ifndef NUMERIC_HPP
#define NUMERIC_HPP

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

class Strike : public Numeric {
   public:
    Strike(double);
};

#endif  // NUMERIC_HPP