#if 0
#ifndef BINOMIALMODELEQUITIES_HPP
#define BINOMIALMODELEQUITIES_HPP

#include "BSDirections.hpp"
#include "BinomialDirections.hpp"
#include "BinomialModel.hpp"
#include "Equities.hpp"

class BinomialModelStock : public BinomialModel {
   private:
    Stock stock;
    BinomialDirections model;
    BSDirections coefficients;

    void buildLattice() override;

   public:
    BinomialModelStock(const Stock &, const BinomialDirections &,
                       const BSDirections &);

    BinomialModelStock(const Stock &, const BSDirections &);
};

#endif  // BINOMIALMODELEQUITIES_HPP
#endif