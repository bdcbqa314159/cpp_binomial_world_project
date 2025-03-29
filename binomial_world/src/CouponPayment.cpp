#include "CouponPayment.hpp"

#include <cassert>

CouponPayment::CouponPayment(double _coupon, double _face_value,
                             size_t _maturity, size_t _coupon_frequency)
    : coupon_parameters(_coupon, _face_value, _maturity, _coupon_frequency) {}

CouponPayment::CouponPayment(const CouponParameters &_coupon_parameters)
    : coupon_parameters(_coupon_parameters) {}

double CouponPayment::operator()(size_t n) const {
    size_t maturity = coupon_parameters.getMaturity();
    size_t coupon_frequency = coupon_parameters.getCouponFrequency();

    assert(n <= maturity);

    if (maturity % coupon_frequency == 0) {
        return coupon_parameters.getCouponPayment();
    } else {
        return 0.;
    }
}

double CouponPayment::getFaceValue() const {
    return coupon_parameters.getFaceValue();
}
size_t CouponPayment::getMaturity() const {
    return coupon_parameters.getFaceValue();
}
size_t CouponPayment::getCouponFrequency() const {
    return coupon_parameters.getCouponFrequency();
}
double CouponPayment::getCoupon() const {
    return coupon_parameters.getCoupon();
}