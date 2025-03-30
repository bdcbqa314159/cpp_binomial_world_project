#pragma once
#ifndef BINOMIAL_WORLD_CALIBRATIONFUNCTIONBDT_HPP
#define BINOMIAL_WORLD_CALIBRATIONFUNCTIONBDT_HPP
#include <vector>

#include "NewtonRaphson.hpp"

class CalibrationFunctionBDT : public Function {
   private:
    std::vector<double> elementary_i;
    double q{}, b{};

   public:
    CalibrationFunctionBDT(const std::vector<double> &, double, double);

    void SetElementary(const std::vector<double> &);

    double Value(double) const override;
    double Derivative(double) const override;
};

#endif  // BINOMIAL_WORLD_CALIBRATIONFUNCTIONBDT_HPP