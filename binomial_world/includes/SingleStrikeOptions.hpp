#pragma once
#ifndef SINGLESTRIKEOPTIONS_HPP
#define SINGLESTRIKEOPTIONS_HPP

#include "Numeric.hpp"
#include "Options.hpp"

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

class InArrearsSingleStrike : public EurOptInArrears {
   protected:
    Strike K;

   public:
    InArrearsSingleStrike(size_t, double);
    double getK() const;
};

class Caplet : public InArrearsSingleStrike {
   public:
    Caplet(size_t, double);
    double payoff(double) const override;
};

class Flooret : public InArrearsSingleStrike {
   public:
    Flooret(size_t, double);
    double payoff(double) const override;
};

#endif  // SINGLESTRIKEOPTIONS_HPP