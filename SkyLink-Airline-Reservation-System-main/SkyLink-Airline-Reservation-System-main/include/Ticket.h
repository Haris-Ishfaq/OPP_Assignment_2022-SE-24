#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <memory>
#include <iostream>

class Passenger;
class Flight;

// Class representing a booked Ticket linking a Passenger to a Flight.
// Shows C++ operator overloading (== and <<) and association between classes.
class Ticket {
private:
    std::string ticketId;
    std::shared_ptr<Passenger> passenger;
    std::shared_ptr<Flight> flight;
    int seatNumber;
    double farePaid;
    std::string bookingStatus; // "Confirmed" or "Cancelled"

public:
    // Parametrized Constructor
    Ticket(const std::string& tId, std::shared_ptr<Passenger> p, std::shared_ptr<Flight> f,
           int seat, double fare, const std::string& status = "Confirmed");

    // Default destructor and copy/move assignments are perfectly managed by the compiler,
    // which is the modern C++ best practice ("Rule of Zero").

    // Getters and Setters
    std::string getTicketId() const;
    std::shared_ptr<Passenger> getPassenger() const;
    std::shared_ptr<Flight> getFlight() const;
    int getSeatNumber() const;
    double getFarePaid() const;
    std::string getBookingStatus() const;
    
    void setBookingStatus(const std::string& status);

    // Operator overloading for duplicate check
    bool operator==(const Ticket& other) const;

    // Friend function for stream insertion operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
};

#endif // TICKET_H
