#ifndef BINOMIALDIRECTIONS_HPP
#define BINOMIALDIRECTIONS_HPP

#include <cstddef>

class BinomialDirections {
   private:
    double U{}, D{};
    size_t N{};

   public:
    BinomialDirections(double _U, size_t _N);
    double getU() const;
    double getD() const;
    size_t getN() const;
};

#endif  // BINOMIALDIRECTIONS_HPP