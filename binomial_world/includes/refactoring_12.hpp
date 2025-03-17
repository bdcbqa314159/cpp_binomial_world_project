#ifndef _REFACTORING_12_HPP_
#define _REFACTORING_12_HPP_

#include "refactoring_10.hpp"
#include "refactoring_9.hpp"

namespace new_code {

class SingleStrike : public EurOption, public AmOption {
   protected:
    double K{};

   public:
    SingleStrike(size_t, double);
    double getK() const;
};
}  // namespace new_code

#endif  //_REFACTORING_12_HPP_