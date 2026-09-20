#ifndef INTERNATIONAL_FLIGHT_H
#define INTERNATIONAL_FLIGHT_H

#include "Flight.h"

// Derived class representing an International Flight
class InternationalFlight : public Flight {
private:
    double basePrice;
    double intlTax;
    double fuelSurcharge;
    bool requiresVisa;

public:
    InternationalFlight(const std::string& flightNum, const std::string& orig, const std::string& dest,
                        const std::string& depTime, int totSeats, int availSeats,
                        double price, double tax, double surcharge, bool visaReq);

    // Overriding base class pure virtual functions
    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getFlightType() const override;
    void print(std::ostream& os) const override;

    // Getters
    double getBasePrice() const;
    double getIntlTax() const;
    double getFuelSurcharge() const;
    bool getRequiresVisa() const;
};

#endif // INTERNATIONAL_FLIGHT_H
