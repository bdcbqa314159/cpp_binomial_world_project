#pragma once

class BinomialDirections
{
private:
    double U{}, D{};

public:
    BinomialDirections() = default;
    BinomialDirections(double);
    double getU() const { return U; }
    double getD() const { return D; }
};