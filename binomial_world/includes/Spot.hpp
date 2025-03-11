#pragma once

class Spot
{
protected:
    double value{};

public:
    Spot() = default;
    Spot(double);
    double operator()() const;
};
