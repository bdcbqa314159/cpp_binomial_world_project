#pragma once
#ifndef BINOMIAL_WORLD_CALIBRATIONPROCESS_HPP
#define BINOMIAL_WORLD_CALIBRATIONPROCESS_HPP
#include <vector>

class InputsCalibration {
    // We are still working with BDT model
   private:
    std::vector<double> observed_spot_rates;
    double q{}, b{};

   public:
    InputsCalibration() = default;
    InputsCalibration(const std::vector<double> &, double, double);

    const std::vector<double> &getObservedSpotRates() const;
    double getQ() const;
    double getB() const;
};

class OutputsCalibration {
   private:
    std::vector<double> a;
    double q{}, b{};

   public:
    OutputsCalibration() = default;
    OutputsCalibration(const std::vector<double> &new_a, double new_q,
                       double new_b);
    const std::vector<double> &getA() const;
    double getQ() const;
    double getB() const;
};

class Calibration {
   private:
    InputsCalibration inputs;
    OutputsCalibration outputs;
    bool calibrated{false};

   public:
    Calibration() = default;
    Calibration(const InputsCalibration &);
    const InputsCalibration &getInputs() const;
    const OutputsCalibration &getOutputs() const;
    void calibrate();
};

#endif  // BINOMIAL_WORLD_CALIBRATIONPROCESS_HPP