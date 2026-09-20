#include "EconomyPassenger.h"

EconomyPassenger::EconomyPassenger(const std::string& id, const std::string& name, const std::string& email)
    : Passenger(id, name, email) {}

double EconomyPassenger::getBaggageAllowance() const {
    return 20.0; // 20 kg limit
}

double EconomyPassenger::getLoyaltyMultiplier() const {
    return 1.0; // Standard multiplier
}

double EconomyPassenger::getCancellationRefundPercentage() const {
    return 50.0; // 50% cancellation fee refund
}

std::string EconomyPassenger::getPassengerType() const {
    return "Economy";
}

void EconomyPassenger::print(std::ostream& os) const {
    Passenger::print(os);
    os << "\nBenefits     : Standard check-in, standard seating.";
}

