#ifndef _REFACTORING_5_HPP_
#define _REFACTORING_5_HPP_

#include <cstddef>

#include "refactoring_1.hpp"

namespace new_code {

class BinomialModelDynamic {
   protected:
    bool lattice_built = false;
    BinomialLattice<double> lattice;

   public:
    BinomialModelDynamic(size_t);
    virtual ~BinomialModelDynamic() = default;
    virtual void buildLattice() = 0;
    const BinomialLattice<double> &getLattice() const;

    virtual double getRiskNeutralProbability() const = 0;
    virtual double getRiskFreeRate() const = 0;

    virtual size_t getN() const = 0;
    virtual double getU() const = 0;
    virtual double getD() const = 0;
    // virtual double initial_value() const = 0;
};

}  // namespace new_code

#endif  //_REFACTORING_5_HPP_