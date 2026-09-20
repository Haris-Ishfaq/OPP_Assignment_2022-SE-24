#include "BusinessPassenger.h"

BusinessPassenger::BusinessPassenger(const std::string& id, const std::string& name, const std::string& email)
    : Passenger(id, name, email) {}

double BusinessPassenger::getBaggageAllowance() const {
    return 35.0; // 35 kg limit
}

double BusinessPassenger::getLoyaltyMultiplier() const {
    return 1.5; // 1.5x loyalty points multiplier
}

double BusinessPassenger::getCancellationRefundPercentage() const {
    return 75.0; // 75% refund upon cancellation
}

std::string BusinessPassenger::getPassengerType() const {
    return "Business";
}

void BusinessPassenger::print(std::ostream& os) const {
    Passenger::print(os);
    os << "\nBenefits     : Business lounge access, priority boarding, extra legroom.";
}

