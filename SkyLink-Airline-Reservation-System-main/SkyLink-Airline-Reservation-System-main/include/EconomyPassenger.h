#ifndef ECONOMY_PASSENGER_H
#define ECONOMY_PASSENGER_H

#include "Passenger.h"

// Derived class for Economy Class Passenger
class EconomyPassenger : public Passenger {
public:
    EconomyPassenger(const std::string& id, const std::string& name, const std::string& email);

    double getBaggageAllowance() const override;
    double getLoyaltyMultiplier() const override;
    double getCancellationRefundPercentage() const override;
    std::string getPassengerType() const override;
    void print(std::ostream& os) const override;
};

#endif // ECONOMY_PASSENGER_H
