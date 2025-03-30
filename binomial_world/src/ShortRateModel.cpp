#include "ShortRateModel.hpp"

ShortRateModel::ShortRateModel(const std::vector<double> &new_a_i, double new_b)
    : a_i(new_a_i), b(new_b) {
    N = a_i.size() - 1;
    r = BinomialLattice<double>(N);
}

void ShortRateModel::buildLattice() {
    double r0 = a_i[0];
    r(0, 0, r0);
    for (size_t i = 1; i < N + 1; i++) {
        for (size_t j = 0; j < i + 1; j++) {
            r(i, j, a_i[i] * exp(b * j));
        }
    }
    latticeBuilt = true;
}

size_t ShortRateModel::getN() const { return N; }

const BinomialLattice<double> &ShortRateModel::getLattice() const {
    assert(latticeBuilt);
    return r;
}