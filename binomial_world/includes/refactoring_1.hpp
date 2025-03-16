#ifndef _REFACTORING_1_HPP_
#define _REFACTORING_1_HPP_
#include <cassert>
#include <iostream>
#include <vector>

namespace new_code {

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
    void operator()(size_t, size_t, const T &);
    T &operator()(size_t, size_t);
    const T &operator()(size_t, size_t) const;
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
void BinomialLattice<T>::operator()(size_t i, size_t j, const T &x) {
    assert(i <= N && j <= i);
    Lattice[i][j] = x;
}

template <typename T>
T &BinomialLattice<T>::operator()(size_t i, size_t j) {
    assert(i <= N && j <= i);
    return Lattice[i][j];
}

template <typename T>
const T &BinomialLattice<T>::operator()(size_t i, size_t j) const {
    assert(i <= N && j <= i);
    return Lattice[i][j];
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

}  // namespace new_code

#endif  // _REFACTORING_HPP_