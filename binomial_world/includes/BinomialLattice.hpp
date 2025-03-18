#ifndef BINOMIALLATTICE_HPP
#define BINOMIALLATTICE_HPP

#include <cassert>
#include <iostream>
#include <vector>

// Fundamental block of the binmomial model - the binomial lattice as a data
// structure

template <typename T>
class BinomialLattice {
   private:
    size_t N{};
    std::vector<std::vector<T>> Lattice;

   public:
    BinomialLattice() = default;
    BinomialLattice(size_t);

    size_t size() const;
    const std::vector<T> &operator[](size_t) const;
    std::vector<T> &operator[](size_t i);
};

template <typename T>
BinomialLattice<T>::BinomialLattice(size_t newN) : N(newN) {
    Lattice.resize(N + 1);
    for (size_t i = 0; i < N + 1; i++) {
        Lattice[i].resize(i + 1);
    }
}

template <typename T>
size_t BinomialLattice<T>::size() const {
    return N;
}

template <typename T>
const std::vector<T> &BinomialLattice<T>::operator[](size_t i) const {
    assert(i <= N);
    return Lattice[i];
}

template <typename T>
std::vector<T> &BinomialLattice<T>::operator[](size_t i) {
    assert(i <= N);
    return Lattice[i];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinomialLattice<T> &Lattice) {
    for (size_t i = 0; i <= Lattice.size(); i++) {
        for (size_t j = 0; j < i + 1; j++) {
            os << Lattice[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

#endif  // BINOMIALLATTICE_HPP