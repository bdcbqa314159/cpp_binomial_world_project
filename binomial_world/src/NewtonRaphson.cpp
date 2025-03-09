#include "NewtonRaphson.hpp"
#include <cmath>

double NewtonRaphson(const Function &f, double target, double guess, double epsilon)
{
    double x_prev = guess;
    double x_next = x_prev - (f.Value(x_prev) - target) / f.Derivative(x_prev);

    while (abs(x_next - x_prev) > epsilon)
    {
        x_prev = x_next;
        x_next = x_prev - (f.Value(x_prev) - target) / f.Derivative(x_prev);
    }
    return x_next;
}