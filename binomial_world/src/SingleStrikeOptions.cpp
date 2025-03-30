#include "SingleStrikeOptions.hpp"

SingleStrike::SingleStrike(size_t newMaturity, double newK)
    : Option(newMaturity),
      EurOption(newMaturity),
      AmOption(newMaturity),
      K(newK) {}

double SingleStrike::getK() const { return K(); }

Call::Call(size_t newMaturity, double newK)
    : Option(newMaturity), SingleStrike(newMaturity, newK) {}

Put::Put(size_t newMaturity, double newK)
    : Option(newMaturity), SingleStrike(newMaturity, newK) {}

double Call::payoff(double z) const { return std::max(z - K(), 0.); }

double Put::payoff(double z) const { return std::max(K() - z, 0.); }

InArrearsSingleStrike::InArrearsSingleStrike(size_t newMaturity, double newK)
    : OptionInArrears(newMaturity),
      EurOptInArrears(newMaturity),
      //   AmOptionInarrears(newMaturity),
      K(newK) {}

double InArrearsSingleStrike::getK() const { return K(); }

Caplet::Caplet(size_t newMaturity, double newK)
    : OptionInArrears(newMaturity), InArrearsSingleStrike(newMaturity, newK) {}

Flooret::Flooret(size_t newMaturity, double newK)
    : OptionInArrears(newMaturity), InArrearsSingleStrike(newMaturity, newK) {}

double Caplet::payoff(double z) const { return std::max(z - K(), 0.); }

double Flooret::payoff(double z) const { return std::max(K() - z, 0.); }
