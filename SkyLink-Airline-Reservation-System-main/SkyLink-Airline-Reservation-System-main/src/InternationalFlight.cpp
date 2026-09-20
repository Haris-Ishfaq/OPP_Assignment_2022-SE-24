#include "InternationalFlight.h"
#include "Exceptions.h"
#include "UIHelper.h"
#include <iostream>
#include <iomanip>

InternationalFlight::InternationalFlight(const std::string& flightNum, const std::string& orig, const std::string& dest,
                                         const std::string& depTime, int totSeats, int availSeats,
                                         double price, double tax, double surcharge, bool visaReq)
    : Flight(flightNum, orig, dest, depTime, totSeats, availSeats),
      basePrice(price), intlTax(tax), fuelSurcharge(surcharge), requiresVisa(visaReq) {
    if (price < 0.0) {
        throw AirlineException("Base price cannot be negative.");
    }
    if (tax < 0.0) {
        throw AirlineException("International tax cannot be negative.");
    }
    if (surcharge < 0.0) {
        throw AirlineException("Fuel surcharge cannot be negative.");
    }
}

double InternationalFlight::calculateBaseFare() const {
    // International pricing: Base Price + International Tax + Fuel Surcharge
    return basePrice + intlTax + fuelSurcharge;
}

void InternationalFlight::displayDetails() const {
    UIHelper::printTableRow({
        flightNumber,
        requiresVisa ? "Int'l (Visa)" : "Int'l",
        origin,
        destination,
        departureTime,
        std::to_string(availableSeats) + " / " + std::to_string(totalSeats),
        "$" + std::to_string(static_cast<int>(calculateBaseFare()))
    }, {10, 13, 14, 14, 18, 11, 9});
}

std::string InternationalFlight::getFlightType() const {
    return "International";
}

double InternationalFlight::getBasePrice() const {
    return basePrice;
}

double InternationalFlight::getIntlTax() const {
    return intlTax;
}

double InternationalFlight::getFuelSurcharge() const {
    return fuelSurcharge;
}

bool InternationalFlight::getRequiresVisa() const {
    return requiresVisa;
}

void InternationalFlight::print(std::ostream& os) const {
    Flight::print(os);
    os << "\nInt'l Tax     : $" << intlTax << "\n"
       << "Fuel Surcharge: $" << fuelSurcharge << "\n"
       << "Visa Required : " << (requiresVisa ? "Yes" : "No");
}

