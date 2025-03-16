#ifndef _REFACTORING_9_HPP_
#define _REFACTORING_9_HPP_

#include "refactoring_5.hpp"
#include "refactoring_8.hpp"

namespace new_code {

class EurOption : public virtual Option {
   public:
    EurOption(size_t);

    double priceByCRR(const BinomialModelDynamic &) const;
};

}  // namespace new_code

#endif  //_REFACTORING_9_HPP_