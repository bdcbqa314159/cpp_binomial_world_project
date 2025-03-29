#pragma once
#ifndef COUPON_PAYMENT_HPP
#define COUPON_PAYMENT_HPP

#include "CouponParameters.hpp"

class CouponPayment {
   private:
    CouponParameters coupon_parameters;

   public:
    CouponPayment(double, double, size_t, size_t = 1);
    CouponPayment(const CouponParameters &);

    double operator()(size_t n) const;

    double getFaceValue() const;
    size_t getMaturity() const;
    size_t getCouponFrequency() const;
    double getCoupon() const;
};

#endif  // COUPON_PAYMENT_HPP