#include "VolGridAdapter.hpp"

#include <cmath>

VolGridAdapter::VolGridAdapter(const BinomialVolGrid &newVolGrid)
    : volGrid(newVolGrid) {
    double dt = getDeltaT();
    double sigma = volGrid.getSigma();
    double u = std::exp(sigma * std::sqrt(dt));
    double d = 1 / u;

    setDirections(u, d);
}

double VolGridAdapter::getSigma() const { return volGrid.getSigma(); }
double VolGridAdapter::getTimeToMaturity() const {
    return volGrid.getTimeToMaturity();
}
size_t VolGridAdapter::getPeriods() const { return volGrid.getPeriods(); }
double VolGridAdapter::getDeltaT() const { return volGrid.getDeltaT(); }
