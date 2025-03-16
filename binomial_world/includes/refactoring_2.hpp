#ifndef _REFACTORING_2_HPP_
#define _REFACTORING_2_HPP_

namespace new_code {

class PrimaryAsset {
   protected:
    double spot{};

   public:
    PrimaryAsset(double);
    double getSpot() const;
    void setSpot(double _spot);
};

class InterestRate : public PrimaryAsset {
   public:
    InterestRate(double);
};

class IRFlat : public InterestRate {
   public:
    IRFlat(double _spot);

    double getR() const;
    void setR(double _r);
};

class IRTermStructure : public InterestRate {
   public:
    IRTermStructure(double);
};

class RiskFreeRateFlat : public IRFlat {
   public:
    RiskFreeRateFlat(double);
};

class RiskFreeRateTerm : public IRTermStructure {
   public:
    RiskFreeRateTerm(double);
};

class Stock : public PrimaryAsset {
   private:
    double div_yield{};

   public:
    Stock(double, double = 0.);

    double getDivYield() const;
    void setDivYield(double _div_yield);
};
}  // namespace new_code

#endif  // _REFACTORING2_HPP_