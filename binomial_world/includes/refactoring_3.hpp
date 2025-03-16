#ifndef _REFACTORING_3_HPP_
#define _REFACTORING_3_HPP_

namespace new_code {
class BinomialDirections {
   private:
    double U{}, D{};

   public:
    BinomialDirections(double _U);
    double getU() const;
    double getD() const;
};
}  // namespace new_code

#endif  // _REFACTORING_3_HPP_