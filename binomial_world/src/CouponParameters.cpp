#include "CouponParameters.hpp"

#include <cassert>

CouponParameters::CouponParameters(double _coupon, double _face_value,
                                   size_t _maturity, size_t _coupon_frequency)
    : coupon(_coupon),
      face_value(_face_value),
      maturity(_maturity),
      coupon_frequency(_coupon_frequency) {
    assert(maturity > 0);
    assert(coupon_frequency > 0);
}

double CouponParameters::getCoupon() const { return coupon(); }
double CouponParameters::getFaceValue() const { return face_value(); }
size_t CouponParameters::getMaturity() const { return maturity; }
size_t CouponParameters::getCouponFrequency() const { return coupon_frequency; }
double CouponParameters::getCouponPayment() const {
    return coupon() * face_value();
}