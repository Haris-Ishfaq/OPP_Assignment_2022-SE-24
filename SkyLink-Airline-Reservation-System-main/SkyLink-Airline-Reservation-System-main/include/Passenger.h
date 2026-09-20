#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <iostream>

// Abstract Base Class representing a Passenger.
// Demonstrates key OOP principles: Encapsulation, Abstraction, and Polymorphism.
class Passenger {
protected:
    std::string passengerId;
    std::string name;
    std::string email;

public:
    Passenger(const std::string& id, const std::string& name, const std::string& email);
    virtual ~Passenger() = default;

    // Getters & Encapsulation
    std::string getPassengerId() const;
    std::string getName() const;
    std::string getEmail() const;

    // Pure virtual functions representing abstraction
    virtual double getBaggageAllowance() const = 0;
    virtual double getLoyaltyMultiplier() const = 0;
    virtual double getCancellationRefundPercentage() const = 0;
    virtual std::string getPassengerType() const = 0;

    // Display passenger information
    virtual void displayDetails() const;

    // Virtual print function for polymorphic stream insertion
    virtual void print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Passenger& passenger);
};

#endif // PASSENGER_H
