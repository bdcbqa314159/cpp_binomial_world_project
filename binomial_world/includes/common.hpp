#pragma once
#include <iostream>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector)
{
    for (auto &elem : vector)
    {
        os << elem << " ";
    }
    return os;
}