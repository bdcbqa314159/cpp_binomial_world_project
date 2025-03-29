#pragma once
#ifndef COUPON_PARAMETERS_HPP
#define COUPON_PARAMETERS_HPP
#include <cstddef>

#include "Numeric.hpp"

class CouponParameters {
   private:
    Coupon coupon;
    FaceValue face_value;
    size_t maturity = 0, coupon_frequency = 1;

   public:
    CouponParameters(double, double, size_t, size_t = 1);

    double getCoupon() const;
    double getFaceValue() const;
    size_t getMaturity() const;
    size_t getCouponFrequency() const;
    double getCouponPayment() const;
};

#endif  // COUPON_PARAMETERS_HPP