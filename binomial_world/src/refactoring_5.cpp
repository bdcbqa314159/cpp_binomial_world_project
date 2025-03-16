#include "refactoring_5.hpp"

#include <cassert>

namespace new_code {

BinomialModelDynamic::BinomialModelDynamic(size_t newN) : lattice(newN) {}

const BinomialLattice<double> &BinomialModelDynamic::getLattice() const {
    assert(lattice_built);
    return lattice;
}

}  // namespace new_code