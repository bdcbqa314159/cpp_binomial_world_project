#pragma once
#ifndef BINOMIAL_LATTICE_TEMPLATE_HPP
#define BINOMIAL_LATTICE_TEMPLATE_HPP

#include "BinomialValues.hpp"

// Fundamental block of the binmomial model - the binomial lattice as a data
// structure

using namespace binomial_values;

namespace binomial_lattice {

template <typename T>
class BinomialLattice {
   private:
    Size N;
    std::vector<std::vector<T>> lattice;

   public:
    BinomialLattice(size_t);
    size_t size() const;

    const std::vector<T> &operator[](size_t) const;
    std::vector<T> &operator[](size_t);
};

template <typename T>
std::ostream &operator<<(std::ostream &, const std::vector<T> &);

template <typename T>
std::ostream &operator<<(std::ostream &, const BinomialLattice<T> &);

template <typename T>
BinomialLattice<T>::BinomialLattice(size_t newN) : N(newN) {
    lattice.resize(N() + 1);
    for (size_t i = 0; i < N() + 1; i++) {
        lattice[i].resize(i + 1);
    }
}

template <typename T>
const std::vector<T> &BinomialLattice<T>::operator[](size_t i) const {
    assert(i <= N());
    return lattice[i];
}

template <typename T>
std::vector<T> &BinomialLattice<T>::operator[](size_t i) {
    assert(i <= N());
    return lattice[i];
}

template <typename T>
size_t BinomialLattice<T>::size() const {
    return N();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinomialLattice<T> &Lattice) {
    for (size_t i = 0; i <= Lattice.size(); i++) {
        os << Lattice[i] << "\n";
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        os << vector[i] << " ";
    }
    return os;
}

}  // namespace binomial_lattice

#endif  // BINOMIAL_LATTICE_TEMPLATE_HPP