#include "CalibrationProcess.hpp"

#include <cassert>
#include <cmath>

#include "BinomialLattice.hpp"
#include "CalibrationFunctionBDT.hpp"
#include "NewtonRaphson.hpp"

InputsCalibration::InputsCalibration(
    const std::vector<double> &new_observed_spot_rates, double new_q,
    double new_b)
    : q(new_q), b(new_b) {
    assert(q >= 0. && q <= 1.);
    assert(b >= 0.);
    if (new_observed_spot_rates[0] != 1.) {
        observed_spot_rates.resize(new_observed_spot_rates.size() + 1);
        observed_spot_rates[0] = 1.;
        for (size_t i = 0; i < new_observed_spot_rates.size(); i++) {
            observed_spot_rates[i + 1] = new_observed_spot_rates[i];
        }
    }
    observed_spot_rates = new_observed_spot_rates;
}

const std::vector<double> &InputsCalibration::getObservedSpotRates() const {
    return observed_spot_rates;
}

double InputsCalibration::getQ() const { return q; }

double InputsCalibration::getB() const { return b; }

OutputsCalibration::OutputsCalibration(const std::vector<double> &new_a,
                                       double new_q, double new_b)
    : a(new_a), q(new_q), b(new_b) {}

const std::vector<double> &OutputsCalibration::getA() const { return a; }

double OutputsCalibration::getQ() const { return q; }

double OutputsCalibration::getB() const { return b; }

Calibration::Calibration(const InputsCalibration &new_inputs)
    : inputs(new_inputs) {}

const InputsCalibration &Calibration::getInputs() const { return inputs; }

const OutputsCalibration &Calibration::getOutputs() const { return outputs; }

void Calibration::calibrate() {
    std::vector<double> observed_spot_rates = inputs.getObservedSpotRates();
    double b = inputs.getB();
    double q = inputs.getQ();
    double p = 1. - q;

    size_t N = observed_spot_rates.size() - 1;
    std::vector<double> a(N);
    a[0] = observed_spot_rates[1];
    std::vector<double> values_to_calibrate(N - 1);

    for (size_t i = 0; i < values_to_calibrate.size(); i++) {
        values_to_calibrate[i] =
            1. / pow((1 + observed_spot_rates[i + 2]), i + 2);
    }

    BinomialLattice<double> r(N);
    BinomialLattice<double> z(N + 1);

    assert(N > 1);
    z[0][0] = 1.;

    double coeff = 1. / (1. + a[0] * exp(b * 0));
    z[1][0] = z[0][0] * q * coeff;
    z[1][1] = z[0][0] * p * coeff;

    CalibrationFunctionBDT my_function({}, q, b);

    for (size_t i = 1; i < N; ++i) {
        my_function.SetElementary(z[i]);
        a[i] = NewtonRaphson(my_function, values_to_calibrate[i - 1], a[i - 1],
                             0.0001);

        size_t i_new = i + 1;
        for (size_t j = 0; j < i_new + 1; j++) {
            if (j == 0) {
                z[i_new][j] =
                    z[i_new - 1][j] * q * 1. / (1. + a[i_new - 1] * exp(b * j));
            } else if (j == i_new) {
                z[i_new][j] = z[i_new - 1][j - 1] * (1. - p) * 1. /
                              (1. + a[i_new - 1] * exp(b * (j - 1)));
            }

            else {
                z[i_new][j] =
                    z[i_new - 1][j - 1] * (1. - p) * 1. /
                        (1. + a[i_new - 1] * exp(b * (j - 1))) +
                    z[i_new - 1][j] * q * 1. / (1. + a[i_new - 1] * exp(b * j));
            }
        }
    }

    outputs = OutputsCalibration(a, q, b);
    calibrated = true;
}
