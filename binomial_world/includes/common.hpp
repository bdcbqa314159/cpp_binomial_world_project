#pragma once
#ifndef BINOMIAL_WORLD_COMMON_HPP
#define BINOMIAL_WORLD_COMMON_HPP
#include <iostream>
#include <vector>

#include "BinomialLattice.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &, const std::vector<T> &);

template <typename T>
std::ostream &operator<<(std::ostream &, const BinomialLattice<T> &);

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
    for (const T &element : vector) {
        os << element << " ";
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinomialLattice<T> &Lattice) {
    for (const std::vector<T> &row : Lattice.getLattice()) {
        os << row << "\n";
    }
    return os;
}

#endif  // BINOMIAL_WORLD_COMMON_HPP