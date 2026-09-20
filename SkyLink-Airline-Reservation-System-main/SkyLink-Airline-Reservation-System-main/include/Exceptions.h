#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// A single custom exception class for the Airline Reservation & Flight Management System.
// This is beginner-friendly and satisfies university OOP requirements for custom exception handling.
class AirlineException : public std::exception {
private:
    std::string message;
public:
    explicit AirlineException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // EXCEPTIONS_H
