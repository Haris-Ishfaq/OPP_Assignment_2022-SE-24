#include "DomesticFlight.h"
#include "Exceptions.h"
#include "UIHelper.h"
#include <iostream>
#include <iomanip>

DomesticFlight::DomesticFlight(const std::string& flightNum, const std::string& orig, const std::string& dest,
                               const std::string& depTime, int totSeats, int availSeats,
                               double price, double tax)
    : Flight(flightNum, orig, dest, depTime, totSeats, availSeats),
      basePrice(price), domesticTax(tax) {
    if (price < 0.0) {
        throw AirlineException("Base price cannot be negative.");
    }
    if (tax < 0.0) {
        throw AirlineException("Domestic tax surcharge cannot be negative.");
    }
}

double DomesticFlight::calculateBaseFare() const {
    // Domestic pricing: Base Price + Domestic Flight Tax
    return basePrice + domesticTax;
}

void DomesticFlight::displayDetails() const {
    UIHelper::printTableRow({
        flightNumber,
        "Domestic",
        origin,
        destination,
        departureTime,
        std::to_string(availableSeats) + " / " + std::to_string(totalSeats),
        "$" + std::to_string(static_cast<int>(calculateBaseFare()))
    }, {10, 13, 14, 14, 18, 11, 9});
}

std::string DomesticFlight::getFlightType() const {
    return "Domestic";
}

double DomesticFlight::getBasePrice() const {
    return basePrice;
}

double DomesticFlight::getDomesticTax() const {
    return domesticTax;
}

void DomesticFlight::print(std::ostream& os) const {
    Flight::print(os);
    os << "\nDomestic Tax  : $" << domesticTax;
}

