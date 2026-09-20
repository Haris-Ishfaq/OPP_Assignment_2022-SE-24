#ifndef BUSINESS_PASSENGER_H
#define BUSINESS_PASSENGER_H

#include "Passenger.h"

// Derived class for Business Class Passenger
class BusinessPassenger : public Passenger {
public:
    BusinessPassenger(const std::string& id, const std::string& name, const std::string& email);

    double getBaggageAllowance() const override;
    double getLoyaltyMultiplier() const override;
    double getCancellationRefundPercentage() const override;
    std::string getPassengerType() const override;
    void print(std::ostream& os) const override;
};

#endif // BUSINESS_PASSENGER_H
