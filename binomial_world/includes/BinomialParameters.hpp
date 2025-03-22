#pragma once
#ifndef BINOMIAL_WORLD_BINOMIALPARAMETERS_HPP
#define BINOMIAL_WORLD_BINOMIALPARAMETERS_HPP

#include <cstddef>

class BinomialParameters {
   public:
    virtual ~BinomialParameters() = default;
    virtual double getU() const = 0;
    virtual double getD() const = 0;
};

class BinomialParametersNoVol : public BinomialParameters {
   private:
    double U{}, D{};

   public:
    BinomialParametersNoVol(double);

    BinomialParametersNoVol(double, double);

    double getU() const override;
    double getD() const override;
};

class BinomialParametersVolGrid : public BinomialParameters {
   private:
    double sigma{}, T{};
    size_t N{};

   public:
    BinomialParametersVolGrid(double, double, size_t);

    double getSigma() const;
    double getT() const;
    size_t getN() const;

    double getDeltaT() const;

    double getU() const override;
    double getD() const override;
};

#endif  // BINOMIAL_WORLD_BINOMIALPARAMETERS_HPP