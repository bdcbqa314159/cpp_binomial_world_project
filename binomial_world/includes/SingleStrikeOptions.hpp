#pragma once
#include "Options.hpp"

class SingleStrike : public EurOption, public AmOption
{
protected:
    double K{};

public:
    // SingleStrike() = default;
    SingleStrike(size_t, double);
    double getK() const { return K; }
};

class Call : public SingleStrike
{

public:
    // Call() = default;
    Call(size_t, double);
    double payoff(double) const override;
};

class Put : public SingleStrike
{

public:
    // Put() = default;
    Put(size_t, double);
    double payoff(double) const override;
};