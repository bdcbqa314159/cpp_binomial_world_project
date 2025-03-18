#ifndef EQUITY_HPP
#define EQUITY_HPP

class Stock {
   private:
    double spot{};
    double div_yield{};

   public:
    Stock(double, double = 0.);

    double getDivYield() const;
    double getSpot() const { return spot; }
    void setDivYield(double _div_yield);
    void setSpot(double _spot);
};

#endif  // EQUITY_HPP