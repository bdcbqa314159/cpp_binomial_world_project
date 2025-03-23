#pragma once
#ifndef BINOMIAL_VALUES_TEMPLATE_HPP
#define BINOMIAL_VALUES_TEMPLATE_HPP

#include <iostream>

// Building block for the values used across the codebase
// T is supposed to be a primitive type

namespace binomial_values {

template <typename T>
class Value {
   protected:
    T value{};

   public:
    Value(T);
    T operator()() const;
    void operator()(T);
};

template <typename T>
std::ostream &operator<<(std::ostream &, const Value<T> &);

// Definitions

template <typename T>
std::ostream &operator<<(std::ostream &os, const Value<T> &myValue) {
    os << myValue();
    return os;
}

template <typename T>
Value<T>::Value(T newValue) : value(newValue) {}

template <typename T>
T Value<T>::operator()() const {
    return value;
}

template <typename T>
void Value<T>::operator()(T newValue) {
    value = newValue;
}

}  // namespace binomial_values

#endif  // BINOMIAL_VALUES_TEMPLATE_HPP