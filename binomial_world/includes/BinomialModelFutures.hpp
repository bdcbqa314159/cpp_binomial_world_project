#ifndef BINOMIALMODEL_FUTURES_HPP
#define BINOMIALMODEL_FUTURES_HPP

#include "BinomialModel.hpp"

class BinomialModelFutures : public BinomialModel {
   private:
    void buildLattice() override;

   public:
    BinomialModelFutures(BinomialModel &);
    double price();
};

#endif  // BINOMIALMODEL_FUTURES_HPP