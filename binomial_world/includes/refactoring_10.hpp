#ifndef _REFACTORING_9_HPP_
#define _REFACTORING_9_HPP_

#include "refactoring_1.hpp"
#include "refactoring_5.hpp"
#include "refactoring_8.hpp"

namespace new_code {

class AmOption : public virtual Option {
   private:
    BinomialLattice<double> priceTree;
    BinomialLattice<bool> stoppingTree;

   public:
    AmOption(size_t);
    double PriceBySnell(const BinomialModelDynamic &);
    const BinomialLattice<double> &getPriceTree() const { return priceTree; }
    const BinomialLattice<bool> &getStopping() const { return stoppingTree; }
};

}  // namespace new_code

#endif  //_REFACTORING_9_HPP_