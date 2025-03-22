#pragma once
#ifndef BINOMIAL_WORLD_REFACTORING_HPP
#define BINOMIAL_WORLD_REFACTORING_HPP

// #include "BinomialLattice.hpp"
// #include "Equities.hpp"
// #include "Spot.hpp"

namespace new_code {

// class RiskFreeRate {
//    protected:
//     Spot spot;

//    public:
//     RiskFreeRate(double);
//     virtual ~RiskFreeRate() = default;
//     virtual double operator()(size_t, size_t) const = 0;
// };

// class RiskFreeRateFlat : public RiskFreeRate {
//    public:
//     RiskFreeRateFlat(double);
//     double operator()(size_t, size_t) const override;
// };

// class BinomialDynamic {
//    protected:
//     size_t N{};
//     double riskNeutralProbability{};
//     BinomialLattice<double> lattice;
//     bool lattice_built = false;

//    public:
//     BinomialDynamic(size_t);
//     virtual double getRFR(size_t, size_t) const = 0;
//     virtual void buildLattice() = 0;
//     double getRiskNeutralProbability() const;
//     size_t getN() const;
//     BinomialLattice<double> getLattice() const;
// };

// class BinomialParameters {
//    public:
//     virtual ~BinomialParameters() = default;
//     virtual double getU() const = 0;
//     virtual double getD() const = 0;
// };

// class BinomialParametersNoVol : public BinomialParameters {
//    private:
//     double U{}, D{};

//    public:
//     BinomialParametersNoVol(double _U) : U(_U) {
//         assert(-1. < U && U < 1.);
//         D = -U / (1. + U);
//     }

//     BinomialParametersNoVol(double _U, double _D) : U(_U), D(_D) {
//         assert(0 < D && D < 1.);
//         assert(0 < U && U < 1.);
//         D = -D;
//     }

//     double getU() const override { return U; }
//     double getD() const override { return D; }
// };

// class BinomialParametersVolGrid : public BinomialParameters {
//    private:
//     double sigma{}, T{};
//     size_t N{};

//    public:
//     BinomialParametersVolGrid(double _sigma, double _T, size_t _N)
//         : sigma(_sigma), T(_T), N(_N) {
//         assert(sigma > 0 && T > 0 && N > 0);
//     }

//     double getU() const override {
//         return std::exp(sigma * std::sqrt(T / N)) - 1;
//     }

//     double getD() const override {
//         double U = getU();
//         return -U / (1. + U);
//     }

//     double getSigma() const { return sigma; }
//     double getT() const { return T; }
//     size_t getN() const { return N; }

//     double getDeltaT() const { return T / N; }
// };

// class MyBinomialModel {
//    private:
//     double U{}, D{};

//    public:
//     MyBinomialModel(double _U, double _D) : U(_U), D(_D) {}
//     MyBinomialModel(const BinomialParameters &params)
//         : U(params.getU()), D(params.getD()) {}

//     double getU() const { return U; }
//     double getD() const { return D; }
// };

// class StockDynamic : public BinomialDynamic {
//    private:
//     Stock stock;
//     RiskFreeRateFlat riskFreeRateFlat;
//     MyBinomialModel model;

//    public:
//     StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
//                  const BinomialParametersNoVol &);

//     StockDynamic(size_t, const Stock &, const RiskFreeRateFlat &,
//                  const BinomialParametersVolGrid &);

//     double getRFR(size_t, size_t) const override;
//     void buildLattice() override;
// };

// class Option {
//    protected:
//     size_t N{};

//    public:
//     Option(size_t);
//     virtual ~Option() = default;
//     size_t getN() const;
//     virtual double payoff(double) const = 0;
// };

// class EurOption : public virtual Option {
//    public:
//     EurOption(size_t);

//     double priceByCRR(BinomialDynamic &) const;
// };

// class AmOption : public virtual Option {
//    private:
//     BinomialLattice<double> priceTree;
//     BinomialLattice<bool> stoppingTree;

//    public:
//     AmOption(size_t);
//     double PriceBySnell(BinomialDynamic &);
//     const BinomialLattice<double> &getPriceTree() const { return priceTree; }
//     const BinomialLattice<bool> &getStopping() const { return stoppingTree; }
// };

// class SingleStrike : public EurOption, public AmOption {
//    protected:
//     double K{};

//    public:
//     SingleStrike(size_t, double);
//     double getK() const;
// };

// class Call : public SingleStrike {
//    public:
//     Call(size_t, double);
//     double payoff(double) const override;
// };

// class Put : public SingleStrike {
//    public:
//     Put(size_t, double);
//     double payoff(double) const override;
// };

// class FuturesDynamic : public BinomialDynamic {
//    private:
//     size_t maturity;
//     BinomialDynamic &primaryAsset;

//    public:
//     FuturesDynamic(size_t, BinomialDynamic &);
//     double getRFR(size_t, size_t) const override;
//     void buildLattice() override;
//     double price() const;
// };

}  // namespace new_code

#endif  // BINOMIAL_WORLD_REFACTORING_HPP