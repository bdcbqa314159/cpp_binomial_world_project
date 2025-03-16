#include "refactoring_7.hpp"

namespace new_code {

// BinomialModelLatticeBuilder::BinomialModelLatticeBuilder(
//     const BinomialModelDynamic &model_stock)
//     : lattice(model_stock.getN()) {
//     double U = model_stock.getU();
//     double D = model_stock.getD();
//     double S0 = model_stock.initial_value();

//     lattice(0, 0) = S0;

//     for (size_t i = 1; i <= model_stock.getN(); i++) {
//         for (size_t j = 0; j < i + 1; j++) {
//             if (j == 0)
//                 lattice(i, j) = lattice(i - 1, j) * (1. + D);
//             else if (j == i)
//                 lattice(i, j) = lattice(i - 1, j - 1) * (1. + U);
//             else
//                 lattice(i, j) = lattice(i - 1, j - 1) * (1. + U);
//         }
//     }
// }

// const BinomialLattice<double> &BinomialModelLatticeBuilder::getLattice()
// const {
//     return lattice;
// }

}  // namespace new_code