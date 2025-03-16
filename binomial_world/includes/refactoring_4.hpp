#ifndef _REFACTORING_4_HPP_
#define _REFACTORING_4_HPP_

#include <cstddef>

#include "refactoring_3.hpp"

namespace new_code {

class BinomialModel {
   private:
    double initial_value{};
    BinomialDirections directions;
    size_t N{};

   public:
    BinomialModel(double, double, size_t);

    double getInitialValue() const;
    double getU() const;
    double getD() const;
    size_t getN() const;
};

}  // namespace new_code

#endif  //_REFACTORING_4_HPP_