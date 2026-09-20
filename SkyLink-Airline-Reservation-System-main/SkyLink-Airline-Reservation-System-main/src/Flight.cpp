#include "Flight.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>

Flight::Flight(const std::string& flightNum, const std::string& orig, const std::string& dest,
               const std::string& depTime, int totSeats, int availSeats)
    : flightNumber(flightNum), origin(orig), destination(dest),
      departureTime(depTime), totalSeats(totSeats), availableSeats(availSeats) {
    if (flightNum.empty()) {
        throw AirlineException("Flight number cannot be empty.");
    }
    if (orig.empty() || dest.empty()) {
        throw AirlineException("Origin and destination cannot be empty.");
    }
    if (orig == dest) {
        throw AirlineException("Origin and destination cannot be the same (" + orig + ").");
    }
    if (totSeats <= 0) {
        throw AirlineException("Total seats capacity must be positive.");
    }
    if (availSeats < 0 || availSeats > totSeats) {
        throw AirlineException("Available seats must be between 0 and total seats capacity.");
    }
}

std::string Flight::getFlightNumber() const {
    return flightNumber;
}

std::string Flight::getOrigin() const {
    return origin;
}

std::string Flight::getDestination() const {
    return destination;
}

std::string Flight::getDepartureTime() const {
    return departureTime;
}

int Flight::getTotalSeats() const {
    return totalSeats;
}

int Flight::getAvailableSeats() const {
    return availableSeats;
}

void Flight::setAvailableSeats(int seats) {
    availableSeats = seats;
}

bool Flight::bookSeat() {
    if (availableSeats > 0) {
        availableSeats--;
        return true;
    }
    return false;
}

bool Flight::releaseSeat() {
    if (availableSeats < totalSeats) {
        availableSeats++;
        return true;
    }
    return false;
}

void Flight::print(std::ostream& os) const {
    os << "Flight Number : " << flightNumber << "\n"
       << "Type          : " << getFlightType() << "\n"
       << "Route         : " << origin << " -> " << destination << "\n"
       << "Departure Time: " << departureTime << "\n"
       << "Seats (A/T)   : " << availableSeats << " / " << totalSeats << "\n"
       << "Base Fare     : $" << calculateBaseFare();
}

std::ostream& operator<<(std::ostream& os, const Flight& flight) {
    flight.print(os);
    return os;
}

