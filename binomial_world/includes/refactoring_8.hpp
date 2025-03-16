#ifndef _REFACTORING_8_HPP_
#define _REFACTORING_8_HPP_
#include <cstddef>

namespace new_code {

class Option {
   protected:
    size_t N{};

   public:
    Option(size_t);
    virtual ~Option() = default;
    size_t getN() const;
    virtual double payoff(double) const = 0;
};

}  // namespace new_code

#endif  //_REFACTORING_8_HPP_