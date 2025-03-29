#pragma once
#ifndef BINOMIALDIRECTIONS_HPP
#define BINOMIALDIRECTIONS_HPP

class BinomialDirections {
   private:
    double u{}, d{};

   public:
    BinomialDirections() = default;
    BinomialDirections(double);
    BinomialDirections(double, double);

    double getU() const;
    double getD() const;

    void setDirections(double, double);
};

#endif  // BINOMIALDIRECTIONS_HPP