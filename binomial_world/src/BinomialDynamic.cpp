#include "BinomialDynamic.hpp"

#include "Utils.hpp"

BinomialDynamic::BinomialDynamic(size_t newPeriods)
    : periods(newPeriods), lattice(newPeriods) {}

double BinomialDynamic::getRiskNeutralProbability() const {
    return riskNeutralProbability();
}

size_t BinomialDynamic::getPeriods() const { return periods; }

const BinomialLattice<double> &BinomialDynamic::getLattice() const {
    return lattice;
}

RiskFreeRateFlat::RiskFreeRateFlat(double newSpot)
    : BinomialDynamic(), shortRate(newSpot) {
    buildLattice();
}

double RiskFreeRateFlat::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return shortRate.getSpot();
}

double RiskFreeRateFlat::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

void RiskFreeRateFlat::buildLattice() {
    lattice[0][0] = shortRate.getSpot();
    lattice_built = true;
}

StockDynamic::StockDynamic(size_t newPeriods, const Stock &newStock,
                           const RiskFreeRateFlat &newRiskFreeRateFlat,
                           const BinomialDirections &newModel)
    : BinomialDynamic(newPeriods),
      stock(newStock),
      riskFreeRateFlat(newRiskFreeRateFlat),
      model(newModel) {
    double u = model.getU();
    double d = model.getD();
    double div_yield = stock.getDivYield();
    // The logic of this is in the resolution of the Exercise 2.10 of the book
    // Stochastic Calculus for Finance I: The Binomial Asset Pricing Model
    // After re reading: the dynamic is impacted by the dividend but not the
    // risk neutral probability
    model.setDirections(u * (1 - div_yield), d * (1 - div_yield));

    double r = riskFreeRateFlat.getRFR(0, 0);

    riskNeutralProbability((1 + r - d) / (u - d));

    buildLattice();
}

StockDynamic::StockDynamic(size_t newPeriods, const Stock &newStock,
                           const RiskFreeRateFlat &newRiskFreeRateFlat,
                           const VolGridAdapter &params)
    : BinomialDynamic(newPeriods),
      stock(newStock),
      riskFreeRateFlat(newRiskFreeRateFlat) {
    double u = params.getU();
    double d = params.getD();
    double div_yield = stock.getDivYield();
    double r = riskFreeRateFlat.getRFR(0, 0);

    double newR = std::exp(r * params.getDeltaT()) - 1;
    riskFreeRateFlat = RiskFreeRateFlat(newR);

    double dt = params.getDeltaT();

    double r_cont = std::exp((r - div_yield) * dt);

    riskNeutralProbability((r_cont - d) / (u - d));
    model.setDirections(u, d);

    buildLattice();
}

void StockDynamic::buildLattice() {
    if (lattice_built) return;

    double initial_value = stock.getSpot();

    latticeBuilder(initial_value, model.getU(), model.getD(), periods, lattice);

    lattice_built = true;
}

double StockDynamic::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return riskFreeRateFlat.getRFR(0, 0);
}

double StockDynamic::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}  // check against dividends

FuturesDynamic::FuturesDynamic(size_t fut_mat, BinomialDynamic &_primaryAsset)
    : BinomialDynamic(fut_mat), maturity(fut_mat), primaryAsset(_primaryAsset) {
    assert(maturity <= primaryAsset.getPeriods());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double FuturesDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

double FuturesDynamic::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

void FuturesDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();
    BinomialLattice<double> primaryLattice = primaryAsset.getLattice();
    size_t N = maturity;

    for (int i = 0; i <= N; ++i) {
        lattice[N][i] =
            primaryLattice[N][i] - primaryAsset.getCouponPayment(N, i);
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            lattice[n][i] =
                q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i];
        }
    }

    lattice_built = true;
}

double FuturesDynamic::price() const {
    assert(lattice_built);
    return lattice[0][0];
}

RiskFreeRateTerm::RiskFreeRateTerm(size_t newPeriods,
                                   const ShortRate &newShortRate,
                                   const BinomialDirections &newModel)
    : BinomialDynamic(newPeriods), shortRate(newShortRate), model(newModel) {
    riskNeutralProbability(0.5);
    buildLattice();
}

void RiskFreeRateTerm::buildLattice() {
    if (lattice_built) return;

    double initial_value = shortRate.getSpot();

    latticeBuilder(initial_value, model.getU(), model.getD(), periods, lattice);

    lattice_built = true;
}

double RiskFreeRateTerm::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return lattice[i][j];
}

double RiskFreeRateTerm::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

ZeroCouponBondDynamic::ZeroCouponBondDynamic(size_t bond_maturity,
                                             RiskFreeRateTerm &_primaryAsset,
                                             double _faceValue)
    : BinomialDynamic(bond_maturity),
      maturity(bond_maturity),
      primaryAsset(_primaryAsset),
      faceValue(_faceValue) {
    assert(maturity <= primaryAsset.getPeriods());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double ZeroCouponBondDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

double ZeroCouponBondDynamic::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

void ZeroCouponBondDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();

    for (int i = 0; i <= maturity; ++i) {
        lattice[maturity][i] = faceValue;
    }

    for (int n = maturity - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double discount_n_i = 1. / (1 + getRFR(n, i));

            lattice[n][i] =
                (q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i]) *
                discount_n_i;
        }
    }
    lattice_built = true;
}

double ZeroCouponBondDynamic::price() const {
    assert(lattice_built);
    return lattice[0][0];
}

CouponBearingBondDynamic::CouponBearingBondDynamic(
    size_t _maturity, RiskFreeRateTerm &_primaryAsset, double _coupon,
    double _face_value, size_t _coupon_frequency)
    : BinomialDynamic(_maturity),
      maturity(_maturity),
      primaryAsset(_primaryAsset),
      couponPayment(_coupon, _face_value, _maturity, _coupon_frequency),
      faceValue(_face_value) {
    assert(maturity <= primaryAsset.getPeriods() + 1);
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double CouponBearingBondDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

double CouponBearingBondDynamic::getCouponPayment(size_t n, size_t i) const {
    assert(i <= n);
    return couponPayment(n);
}

void CouponBearingBondDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();

    for (int i = 0; i <= maturity; ++i) {
        lattice[maturity][i] = faceValue + couponPayment(i);
    }

    for (int n = maturity - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double discount_n_i = 1. / (1 + getRFR(n, i));

            lattice[n][i] =
                (q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i]) *
                    discount_n_i +
                couponPayment(i);
        }
    }
    lattice_built = true;
}

double CouponBearingBondDynamic::price() const {
    assert(lattice_built);
    return lattice[0][0];
}

ForwardsDynamic::ForwardsDynamic(size_t fut_mat, BinomialDynamic &_primaryAsset)
    : BinomialDynamic(fut_mat), maturity(fut_mat), primaryAsset(_primaryAsset) {
    assert(maturity <= primaryAsset.getPeriods());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double ForwardsDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

double ForwardsDynamic::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

void ForwardsDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();
    BinomialLattice<double> primaryLattice = primaryAsset.getLattice();
    size_t N = maturity;

    for (int i = 0; i <= N; ++i) {
        lattice[N][i] =
            primaryLattice[N][i] - primaryAsset.getCouponPayment(N, i);
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double discount_n_i = 1. / (1 + primaryAsset.getRFR(n, i));
            lattice[n][i] =
                (q * lattice[n + 1][i + 1] + (1. - q) * lattice[n + 1][i]) *
                discount_n_i;
        }
    }

    lattice_built = true;
}

double ForwardsDynamic::price() const {
    assert(lattice_built);

    double zcbPriceDelivery = zeroCouponBondPrice(primaryAsset, maturity);

    return lattice[0][0] / zcbPriceDelivery;
}

SwapDynamic::SwapDynamic(size_t swap_mat, BinomialDynamic &_primaryAsset,
                         double _fixedRate)
    : BinomialDynamic(swap_mat - 1),
      maturity(swap_mat - 1),
      primaryAsset(_primaryAsset),
      fixedRate(_fixedRate) {
    assert(maturity <= primaryAsset.getPeriods());
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    buildLattice();
}

double SwapDynamic::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

double SwapDynamic::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return (getRFR(i, j) - fixedRate);
}

void SwapDynamic::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();
    BinomialLattice<double> primaryLattice = primaryAsset.getLattice();
    size_t N = maturity;

    for (int i = 0; i <= N; ++i) {
        double discount_N_i = 1. / (1 + primaryAsset.getRFR(N, i));
        lattice[N][i] = getCouponPayment(N, i) * discount_N_i;
    }

    for (int n = N - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double discount_n_i = 1. / (1 + primaryAsset.getRFR(n, i));
            lattice[n][i] =
                (getCouponPayment(n, i) + q * lattice[n + 1][i + 1] +
                 (1. - q) * lattice[n + 1][i]) *
                discount_n_i;
        }
    }

    lattice_built = true;
}

double SwapDynamic::price() const {
    assert(lattice_built);

    return lattice[0][0];
}

ElementaryPrices::ElementaryPrices(RiskFreeRateTerm &_primaryAsset)
    : BinomialDynamic(_primaryAsset.getPeriods() + 1),
      maturity(_primaryAsset.getPeriods()),
      primaryAsset(_primaryAsset) {
    riskNeutralProbability = primaryAsset.getRiskNeutralProbability();
    zcb.resize(maturity + 2);
    spotRates.resize(maturity + 2);
    buildLattice();
    buildRates();
}

double ElementaryPrices::getRFR(size_t n, size_t i) const {
    return primaryAsset.getRFR(n, i);
}

double ElementaryPrices::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

void ElementaryPrices::buildLattice() {
    if (lattice_built) return;

    double q = riskNeutralProbability();

    lattice[0][0] = 1.;

    for (size_t i = 1; i < maturity + 2; i++) {
        for (size_t j = 0; j < i + 1; j++) {
            if (j == 0) {
                lattice[i][j] = lattice[i - 1][j] * q * 1. /
                                (1. + primaryAsset.getRFR(i - 1, j));

            } else if (j == i) {
                lattice[i][j] = lattice[i - 1][j - 1] * (1. - q) * 1. /
                                (1. + primaryAsset.getRFR(i - 1, j - 1));
            }

            else {
                lattice[i][j] = lattice[i - 1][j - 1] * (1. - q) * 1. /
                                    (1. + primaryAsset.getRFR(i - 1, j - 1)) +
                                lattice[i - 1][j] * q * 1. /
                                    (1. + primaryAsset.getRFR(i - 1, j));
            }
        }
    }
    lattice_built = true;
}

void ElementaryPrices::buildRates() {
    zcb[0] = 1.;
    for (size_t i = 1; i < maturity + 2; i++) {
        zcb[i] = 0.;
        for (size_t j = 0; j < i + 1; j++) zcb[i] += lattice[i][j];
    }

    spotRates[0] = 1.;
    for (size_t i = 1; i < maturity + 2; i++) {
        double a = 1. / zcb[i];
        double b = 1. / i;

        spotRates[i] = (pow(a, b) - 1.);
    }
}

const std::vector<double> &ElementaryPrices::getZCB() const {
    assert(lattice_built);
    return zcb;
}

const std::vector<double> &ElementaryPrices::getSpotRates() const {
    assert(lattice_built);
    return spotRates;
}

std::unique_ptr<BinomialModelParameters> BDTParameters::clone() const {
    return std::make_unique<BDTParameters>(*this);
}

BDTParameters::BDTParameters(const std::vector<double> &_a_i, double _b)
    : a_i(_a_i), b(_b) {
    assert(a_i.size() > 0);
}

void BDTParameters::buildLattice(BinomialLattice<double> &lattice) {
    size_t N = a_i.size() - 1;

    assert(N == lattice.getPeriods());
    lattice[0][0] = a_i[0];

    for (size_t i = 1; i < N + 1; i++) {
        for (size_t j = 0; j < i + 1; j++) {
            lattice[i][j] = a_i[i] * exp(b * j);
        }
    }
}
const std::vector<double> &BDTParameters::getSpotRates() const { return a_i; }

double BDTParameters::getB() const { return b; }

RiskFreeRateTermModel::RiskFreeRateTermModel(
    size_t newPeriods, const ShortRate &newShortRate,
    const BinomialModelParameters &newModel)
    : BinomialDynamic(newPeriods),
      shortRate(newShortRate),
      model(std::move(newModel.clone())) {
    assert(newPeriods > 0);
    buildLattice();
}

double RiskFreeRateTermModel::getRFR(size_t i, size_t j) const {
    assert(j <= i);
    return lattice[i][j];
}

double RiskFreeRateTermModel::getCouponPayment(size_t i, size_t j) const {
    assert(j <= i);
    return 0.;
}

void RiskFreeRateTermModel::buildLattice() {
    if (lattice_built) return;

    double initial_value = shortRate.getSpot();

    model->buildLattice(lattice);

    lattice_built = true;
}
