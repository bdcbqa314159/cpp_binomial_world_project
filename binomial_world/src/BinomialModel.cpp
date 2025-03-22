#include "BinomialModel.hpp"

// BinomialModel::BinomialModel(size_t _N) : N(_N), lattice(N) {}

// double BinomialModel::getRiskNeutralProbability() const {
//     return riskNeutralProbability;
// }
// double BinomialModel::getRiskFreeRate() const { return riskFreeRate; }
// size_t BinomialModel::getN() const { return N; }

// const BinomialLattice<double> &BinomialModel::getLattice() const {
//     return lattice;
// }

MyBinomialModel::MyBinomialModel(double _U, double _D) : U(_U), D(_D) {}
MyBinomialModel::MyBinomialModel(const BinomialParameters &params)
    : U(params.getU()), D(params.getD()) {}

double MyBinomialModel::getU() const { return U; }
double MyBinomialModel::getD() const { return D; }