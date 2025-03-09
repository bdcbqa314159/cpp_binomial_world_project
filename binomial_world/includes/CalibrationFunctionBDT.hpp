#pragma once
#include "NewtonRaphson.hpp"
#include <vector>
#include <cmath>

class CalibrationFunctionBDT : public Function
{
private:
    std::vector<double> elementary_i;
    double q{}, b{};

public:
    CalibrationFunctionBDT(const std::vector<double> &, double, double);

    void SetElementary(const std::vector<double> &);

    double Value(double) const override;
    double Derivative(double) const override;
};