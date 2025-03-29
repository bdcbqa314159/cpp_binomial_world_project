#pragma once
#ifndef BINOMIALLATTICE_HPP
#define BINOMIALLATTICE_HPP

#include <cassert>
#include <cstddef>
#include <vector>

// Fundamental block of the binmomial model - the binomial lattice as a data
// structure
template <typename T>
class BinomialLattice {
   private:
    size_t periods{};
    std::vector<std::vector<T>> lattice;

   public:
    BinomialLattice(size_t);
    size_t getPeriods() const;
    const std::vector<std::vector<T>> &getLattice() const;

    const std::vector<T> &operator[](size_t) const;
    std::vector<T> &operator[](size_t);
};

template <typename T>
BinomialLattice<T>::BinomialLattice(size_t newPeriods) : periods(newPeriods) {
    lattice.resize(periods + 1);
    for (size_t i = 0; i <= periods; i++) {
        lattice[i].resize(i + 1);
    }
}

template <typename T>
const std::vector<T> &BinomialLattice<T>::operator[](size_t i) const {
    assert(i <= periods);
    return lattice[i];
}

template <typename T>
std::vector<T> &BinomialLattice<T>::operator[](size_t i) {
    assert(i <= periods);
    return lattice[i];
}

template <typename T>
size_t BinomialLattice<T>::getPeriods() const {
    return periods;
}

template <typename T>
const std::vector<std::vector<T>> &BinomialLattice<T>::getLattice() const {
    return lattice;
}

#endif  // BINOMIALLATTICE_HPP