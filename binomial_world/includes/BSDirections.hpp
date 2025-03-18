#ifndef BSDIRECTIONS_HPP
#define BSDIRECTIONS_HPP

#include <cstddef>

class BSDirections {
   private:
    double r{}, sigma{}, T{};
    size_t N{};
    bool no_diffusion = true;

   public:
    BSDirections(double);
    BSDirections(double, double, double, size_t);
    double getR() const;
    double getSigma() const;
    double getT() const;
    size_t getN() const;
    bool onlyDrift() const;
    double getU() const;
};

#endif  // BSDIRECTIONS_HPP