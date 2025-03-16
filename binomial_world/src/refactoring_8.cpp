#include "refactoring_8.hpp"

namespace new_code {

Option::Option(size_t newN) : N(newN) {}
size_t Option::getN() const { return N; }

}  // namespace new_code