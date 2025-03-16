#include "refactoring_4.hpp"

namespace new_code {

BinomialModel::BinomialModel(double _initial_value, double _U, size_t _N)
    : initial_value(_initial_value), directions(_U), N(_N) {}

double BinomialModel::getInitialValue() const { return initial_value; }
double BinomialModel::getU() const { return directions.getU(); }
double BinomialModel::getD() const { return directions.getD(); }
size_t BinomialModel::getN() const { return N; }

}  // namespace new_code