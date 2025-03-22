#include "Spot.hpp"

Spot::Spot(double _value) : value(_value) {}
double Spot::operator()() const { return value; }
void Spot::operator()(double _value) { value = _value; }
std::ostream &operator<<(std::ostream &os, const Spot &spot) {
    os << spot();
    return os;
}