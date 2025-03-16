#ifndef _REFACTORING_6_HPP_
#define _REFACTORING_6_HPP_

#include "refactoring_2.hpp"
#include "refactoring_4.hpp"
#include "refactoring_5.hpp"

namespace new_code {

class BinomialModelStock : public BinomialModelDynamic {
   private:
    Stock stock;
    BinomialModel model;
    double riskFreeRate{};
    double riskNeutralProbability{};

   public:
    BinomialModelStock(const Stock &, double U, size_t, double);
    double getRiskNeutralProbability() const override;
    double getRiskFreeRate() const override;
    void buildLattice() override;

    size_t getN() const override;
    double getU() const override;
    double getD() const override;
    // double initial_value() const override;
};

}  // namespace new_code

#endif  //_REFACTORING_6_HPP_