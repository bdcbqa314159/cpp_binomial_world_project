#ifndef _REFACTORING_5_HPP_
#define _REFACTORING_5_HPP_

#include <cstddef>

namespace new_code {

class BinomialModelDynamic {
   public:
    virtual double getRiskNeutralProbability() const = 0;
    virtual double getRiskFreeRate() const = 0;

    virtual size_t getN() const = 0;
    virtual double getU() const = 0;
    virtual double getD() const = 0;
    virtual double initial_value() const = 0;
};

}  // namespace new_code

#endif  //_REFACTORING_5_HPP_