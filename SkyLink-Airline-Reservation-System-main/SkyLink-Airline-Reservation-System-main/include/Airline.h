#ifndef AIRLINE_H
#define AIRLINE_H

#include <vector>
#include <memory>
#include <string>
#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"

// Controller class aggregating Flights, Passengers, and Tickets
class Airline {
private:
    std::vector<std::shared_ptr<Flight>> flights;
    std::vector<std::shared_ptr<Passenger>> passengers;
    std::vector<std::shared_ptr<Ticket>> tickets;

public:
    Airline() = default;

    // Flight Management
    void addFlight(std::shared_ptr<Flight> flight);
    bool removeFlight(const std::string& flightNo);
    std::shared_ptr<Flight> findFlight(const std::string& flightNo) const;
    void listFlights() const;

    // Passenger Management
    void registerPassenger(std::shared_ptr<Passenger> passenger);
    bool removePassenger(const std::string& passengerId);
    std::shared_ptr<Passenger> findPassenger(const std::string& passengerId) const;
    void listPassengers() const;

    // Booking System
    std::shared_ptr<Ticket> bookTicket(const std::string& passengerId, const std::string& flightNo, int seatNo = 0);
    
    // Seat Map
    void showSeatMap(const std::string& flightNo) const;
    
    // Cancellation System
    void cancelTicket(const std::string& ticketId);
    
    // Ticket Management
    void listTickets() const;
    std::shared_ptr<Ticket> findTicket(const std::string& ticketId) const;

    // Reports System
    void showTodayDepartures(const std::string& date) const;
    void showOccupancyPercentage() const;
    void showTopRevenueFlights() const;
    void showMonthlyRevenueReport(const std::string& monthYear) const;

    // File Handling
    void saveData(const std::string& flightsFile, const std::string& passengersFile, const std::string& ticketsFile) const;
    void loadData(const std::string& flightsFile, const std::string& passengersFile, const std::string& ticketsFile);

    // Getters for STL containers
    const std::vector<std::shared_ptr<Flight>>& getFlights() const;
    const std::vector<std::shared_ptr<Passenger>>& getPassengers() const;
    const std::vector<std::shared_ptr<Ticket>>& getTickets() const;
};

#endif // AIRLINE_H
