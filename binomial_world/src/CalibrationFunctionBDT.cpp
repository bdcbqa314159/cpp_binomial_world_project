#include "CalibrationFunctionBDT.hpp"

CalibrationFunctionBDT::CalibrationFunctionBDT(const std::vector<double> &elementary, double q, double b) : elementary_i(elementary), q(q), b(b) {}

void CalibrationFunctionBDT::SetElementary(const std::vector<double> &elementary) { elementary_i = elementary; }

double CalibrationFunctionBDT::Value(double x) const
{
    size_t N = elementary_i.size();

    double sum = 0.;
    for (size_t i = 0; i < N; i++)
    {
        double D = 1. / (100. + x * exp(b * i));
        sum += elementary_i[i] * D;
    }
    sum = 200 * q * sum;
    return sum;
}

double CalibrationFunctionBDT::Derivative(double x) const
{
    size_t N = elementary_i.size();

    double sum = 0.;
    for (size_t i = 0; i < N; i++)
    {
        double D = 1. / pow(100. + x * exp(b * i), 2);
        sum -= (elementary_i[i] * exp(b * i) * D);
    }
    sum = 200 * q * sum;
    return sum;
}