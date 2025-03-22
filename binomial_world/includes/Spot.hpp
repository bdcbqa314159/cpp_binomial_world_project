#pragma once
#ifndef BINOMIAL_WORLD_SPOT_HPP
#define BINOMIAL_WORLD_SPOT_HPP

#include <iostream>

class Spot {
   private:
    double value{};

   public:
    Spot(double);
    double operator()() const;
    void operator()(double);
};

std::ostream &operator<<(std::ostream &, const Spot &);

#endif  // BINOMIAL_WORLD_SPOT_HPP
