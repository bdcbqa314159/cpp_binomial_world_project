#pragma once
#ifndef BINOMIAL_WORLD_NEWTONRAPHSON_HPP
#define BINOMIAL_WORLD_NEWTONRAPHSON_HPP

class Function {
   public:
    virtual double Value(double) const = 0;
    virtual double Derivative(double) const = 0;
};

double NewtonRaphson(const Function &, double, double, double = 0.0001);

#endif  // BINOMIAL_WORLD_NEWTONRAPHSON_HPP