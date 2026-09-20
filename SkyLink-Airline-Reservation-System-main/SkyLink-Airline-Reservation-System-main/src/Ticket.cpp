#include "Ticket.h"
#include "Passenger.h"
#include "Flight.h"
#include "Exceptions.h"
#include <iomanip>

Ticket::Ticket(const std::string& tId, std::shared_ptr<Passenger> p, std::shared_ptr<Flight> f,
               int seat, double fare, const std::string& status)
    : ticketId(tId), passenger(p), flight(f), seatNumber(seat), farePaid(fare), bookingStatus(status) {
    if (tId.empty()) {
        throw AirlineException("Ticket ID cannot be empty.");
    }
    if (!p) {
        throw AirlineException("Passenger pointer cannot be null in Ticket.");
    }
    if (!f) {
        throw AirlineException("Flight pointer cannot be null in Ticket.");
    }
    if (seat <= 0) {
        throw AirlineException("Seat number must be greater than zero.");
    }
    if (fare < 0.0) {
        throw AirlineException("Fare paid cannot be negative.");
    }
}

std::string Ticket::getTicketId() const {
    return ticketId;
}

std::shared_ptr<Passenger> Ticket::getPassenger() const {
    return passenger;
}

std::shared_ptr<Flight> Ticket::getFlight() const {
    return flight;
}

int Ticket::getSeatNumber() const {
    return seatNumber;
}

double Ticket::getFarePaid() const {
    return farePaid;
}

std::string Ticket::getBookingStatus() const {
    return bookingStatus;
}

void Ticket::setBookingStatus(const std::string& status) {
    bookingStatus = status;
}

bool Ticket::operator==(const Ticket& other) const {
    if (!passenger || !other.passenger || !flight || !other.flight) {
        return false;
    }
    // Duplicate booking is defined as same passenger on the same flight
    return (passenger->getPassengerId() == other.passenger->getPassengerId()) &&
           (flight->getFlightNumber() == other.flight->getFlightNumber());
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << "===============================================\n"
       << "                 BOARDING PASS                 \n"
       << "===============================================\n"
       << " Ticket ID    : " << ticket.ticketId << "\n"
       << " Status       : " << ticket.bookingStatus << "\n"
       << " Passenger ID : " << (ticket.passenger ? ticket.passenger->getPassengerId() : "N/A") << "\n"
       << " Name         : " << (ticket.passenger ? ticket.passenger->getName() : "N/A") << "\n"
       << " Type         : " << (ticket.passenger ? ticket.passenger->getPassengerType() : "N/A") << "\n"
       << "-----------------------------------------------\n"
       << " Flight No    : " << (ticket.flight ? ticket.flight->getFlightNumber() : "N/A") << "\n"
       << " Route        : " << (ticket.flight ? ticket.flight->getOrigin() : "N/A") << " -> " 
       << (ticket.flight ? ticket.flight->getDestination() : "N/A") << "\n"
       << " Departure    : " << (ticket.flight ? ticket.flight->getDepartureTime() : "N/A") << "\n"
       << " Seat Number  : " << ticket.seatNumber << "\n"
       << " Fare Paid    : $" << std::fixed << std::setprecision(2) << ticket.farePaid << "\n"
       << "===============================================";
    return os;
}
