#ifndef DOMESTIC_FLIGHT_H
#define DOMESTIC_FLIGHT_H

#include "Flight.h"

// Derived class representing a Domestic Flight
class DomesticFlight : public Flight {
private:
    double basePrice;
    double domesticTax;

public:
    DomesticFlight(const std::string& flightNum, const std::string& orig, const std::string& dest,
                   const std::string& depTime, int totSeats, int availSeats,
                   double price, double tax);

    // Overriding base class pure virtual functions
    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getFlightType() const override;
    void print(std::ostream& os) const override;

    // Getters
    double getBasePrice() const;
    double getDomesticTax() const;
};

#endif // DOMESTIC_FLIGHT_H
