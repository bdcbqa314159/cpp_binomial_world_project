#include "Utils.hpp"

void latticeBuilder(double initial_value, double u, double d, size_t periods,
                    BinomialLattice<double> &lattice) {
    lattice[0][0] = initial_value;

    for (size_t i = 1; i <= periods; i++) {
        for (size_t j = 0; j < i + 1; j++) {
            if (j == 0)
                lattice[i][j] = lattice[i - 1][j] * d;
            else
                lattice[i][j] = lattice[i - 1][j - 1] * u;
        }
    }
}