#ifndef _REFACTORING_11_HPP_
#define _REFACTORING_11_HPP_

#include <cstddef>

#include "refactoring_5.hpp"

namespace new_code {

class Futures : public BinomialModelDynamic {
   private:
    double q{};
    double r{};
    double u{};
    double d{};
    size_t N{};

   public:
    Futures(BinomialModelDynamic &);
    void buildLattice() override;

    double getRiskNeutralProbability() const override;
    double getRiskFreeRate() const override;

    size_t getN() const override;
    double getU() const override;
    double getD() const override;
    double price();
};

}  // namespace new_code

#endif  //_REFACTORING_11_HPP_