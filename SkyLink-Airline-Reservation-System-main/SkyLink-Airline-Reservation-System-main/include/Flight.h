#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

// Abstract Base Class representing a Flight
class Flight {
protected:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    int totalSeats;
    int availableSeats;

public:
    // Constructor
    Flight(const std::string& flightNum, const std::string& orig, const std::string& dest,
           const std::string& depTime, int totSeats, int availSeats);
    
    // Virtual destructor to prevent memory leaks in derived classes
    virtual ~Flight() = default;

    // Pure virtual functions representing abstraction
    virtual double calculateBaseFare() const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string getFlightType() const = 0;

    // Virtual print function for polymorphic stream insertion
    virtual void print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Flight& flight);

    // Getters & Encapsulation
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureTime() const;
    int getTotalSeats() const;
    int getAvailableSeats() const;

    // Helper functions for seat management
    void setAvailableSeats(int seats);
    bool bookSeat();
    bool releaseSeat();
};

#endif // FLIGHT_H
