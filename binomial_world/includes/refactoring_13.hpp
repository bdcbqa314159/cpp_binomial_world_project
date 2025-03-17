#ifndef _REFACTORING_13_HPP_
#define _REFACTORING_13_HPP_

#include "refactoring_12.hpp"

namespace new_code {

class Call : public SingleStrike {
   public:
    Call(size_t, double);
    double payoff(double) const override;
};

class Put : public SingleStrike {
   public:
    Put(size_t, double);
    double payoff(double) const override;
};
}  // namespace new_code

#endif  //_REFACTORING_13_HPP_