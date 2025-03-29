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

double zeroCouponBondPrice(const BinomialDynamic &primaryAsset, size_t maturity,
                           double faceValue) {
    size_t my_mat = 4;
    double my_fv = 100.;
    BinomialLattice<double> my_lattice(maturity);
    assert(maturity <= primaryAsset.getPeriods() + 1);

    double q = primaryAsset.getRiskNeutralProbability();

    for (int i = 0; i <= maturity; ++i) {
        my_lattice[maturity][i] = 1. * faceValue;
    }

    for (int n = maturity - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double discount_n_i = 1. / (1 + primaryAsset.getRFR(n, i));

            my_lattice[n][i] = (q * my_lattice[n + 1][i + 1] +
                                (1. - q) * my_lattice[n + 1][i]) *
                               discount_n_i;
        }
    }

    return my_lattice[0][0];
}