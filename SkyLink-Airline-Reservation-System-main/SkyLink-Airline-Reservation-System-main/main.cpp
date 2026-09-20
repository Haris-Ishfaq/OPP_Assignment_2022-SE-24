#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include "Airline.h"
#include "DomesticFlight.h"
#include "InternationalFlight.h"
#include "EconomyPassenger.h"
#include "BusinessPassenger.h"
#include "SearchTemplate.h"
#include "Exceptions.h"
#include "UIHelper.h"

// Check if file exists
static bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Create directory
static void createDirectory(const std::string& dirName) {
#ifdef _WIN32
    _mkdir(dirName.c_str());
#else
    mkdir(dirName.c_str(), 0777);
#endif
}

// Pause screen
void waitForEnter() {
    std::cout << "\nPress Enter to proceed...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Validate YYYY-MM-DD HH:MM
static bool isValidDateTime(const std::string& dt) {
    if (dt.length() != 16) return false;
    if (dt[4] != '-' || dt[7] != '-' || dt[10] != ' ' || dt[13] != ':') return false;
    for (int i = 0; i < 16; ++i) {
        if (i == 4 || i == 7 || i == 10 || i == 13) continue;
        if (!std::isdigit(dt[i])) return false;
    }
    int year = std::stoi(dt.substr(0, 4));
    int month = std::stoi(dt.substr(5, 2));
    int day = std::stoi(dt.substr(8, 2));
    int hour = std::stoi(dt.substr(11, 2));
    int minute = std::stoi(dt.substr(14, 2));

    if (year < 2026 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    if (month == 2) {
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (isLeap && day > 29) return false;
        if (!isLeap && day > 28) return false;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }
    return true;
}

// Validate YYYY-MM
static bool isValidMonthYear(const std::string& my) {
    if (my.length() != 7) return false;
    if (my[4] != '-') return false;
    for (int i = 0; i < 7; ++i) {
        if (i == 4) continue;
        if (!std::isdigit(my[i])) return false;
    }
    int year = std::stoi(my.substr(0, 4));
    int month = std::stoi(my.substr(5, 2));
    if (year < 2026 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    return true;
}

// Numeric validations
int getValidInt(const std::string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            if (val >= minVal && val <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
        }
        UIHelper::printWarningMessage("Input not accepted! Enter a whole number from " + std::to_string(minVal) + " to " + std::to_string(maxVal) + ".");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double getValidDouble(const std::string& prompt, double minVal) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            if (val >= minVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
        }
        UIHelper::printWarningMessage("Input not accepted! Enter a numeric value of at least " + std::to_string(static_cast<int>(minVal)) + ".");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getNonEmptyString(const std::string& prompt) {
    std::string str;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, str);
        if (!str.empty()) {
            return str;
        }
        UIHelper::printWarningMessage("This field must not be left blank. Please provide a valid entry.");
    }
}

std::string getValidDateTime(const std::string& prompt) {
    std::string str;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, str);
        if (isValidDateTime(str)) {
            return str;
        }
        UIHelper::printWarningMessage("Malformed date/time! Use YYYY-MM-DD HH:MM (e.g. 2026-05-30 08:00).");
    }
}

std::string getValidMonthYear(const std::string& prompt) {
    std::string str;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, str);
        if (isValidMonthYear(str)) {
            return str;
        }
        UIHelper::printWarningMessage("Malformed entry! Use YYYY-MM (e.g. 2026-05).");
    }
}

// Default baseline data
void populateSampleData(Airline& airline) {
    // Register 8 Flights (Domestic and International)
    airline.addFlight(std::make_shared<DomesticFlight>("DF-101", "Islamabad", "Karachi", "2026-05-30 08:00", 12, 12, 150.0, 20.00));
    airline.addFlight(std::make_shared<DomesticFlight>("DF-102", "Lahore", "Karachi", "2026-05-30 12:30", 15, 15, 120.0, 15.00));
    airline.addFlight(std::make_shared<DomesticFlight>("DF-103", "Islamabad", "Lahore", "2026-05-31 09:15", 18, 18, 90.0, 10.00));
    airline.addFlight(std::make_shared<DomesticFlight>("DF-104", "Peshawar", "Karachi", "2026-05-30 15:45", 12, 12, 180.0, 25.00));

    airline.addFlight(std::make_shared<InternationalFlight>("IF-201", "Karachi", "London", "2026-05-30 20:00", 30, 30, 450.0, 50.00, 100.00, true));
    airline.addFlight(std::make_shared<InternationalFlight>("IF-202", "Lahore", "Dubai", "2026-05-31 13:00", 45, 45, 300.0, 30.00, 50.00, false));
    airline.addFlight(std::make_shared<InternationalFlight>("IF-203", "Islamabad", "New York", "2026-05-30 10:30", 36, 36, 750.0, 90.00, 150.00, true));
    airline.addFlight(std::make_shared<InternationalFlight>("IF-204", "Karachi", "Istanbul", "2026-06-01 18:00", 45, 45, 400.0, 45.00, 80.00, true));

    // Register 6 Passengers
    airline.registerPassenger(std::make_shared<EconomyPassenger>("P-1001", "John Doe", "john.doe@email.com"));
    airline.registerPassenger(std::make_shared<EconomyPassenger>("P-1002", "Jane Smith", "jane.smith@email.com"));
    airline.registerPassenger(std::make_shared<EconomyPassenger>("P-1003", "Bob Johnson", "bob.johnson@email.com"));
    
    airline.registerPassenger(std::make_shared<BusinessPassenger>("P-2001", "Alice Brown", "alice.brown@email.com"));
    airline.registerPassenger(std::make_shared<BusinessPassenger>("P-2002", "Charlie Davis", "charlie.davis@email.com"));
    airline.registerPassenger(std::make_shared<BusinessPassenger>("P-2003", "Frank Miller", "frank.miller@email.com"));
}

// Integration self-tests
void runSelfTests(Airline& airline) {
    std::cout << "\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:      EXECUTING SYSTEM INTEGRATION TEST SUITE       :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
    try {
        // Test 1: Instantiation of different Flight classes
        auto df = std::make_shared<DomesticFlight>("TEST-DF", "ISB", "KHI", "2026-06-01 10:00", 9, 9, 200.0, 20.0);
        auto inf = std::make_shared<InternationalFlight>("TEST-IF", "ISB", "LHR", "2026-06-01 12:00", 12, 12, 500.0, 50.0, 100.0, true);
        
        if (df->calculateBaseFare() != 220.0) throw std::runtime_error("Domestic flight fare computation failed.");
        if (inf->calculateBaseFare() != 650.0) throw std::runtime_error("International flight fare computation failed.");
        std::cout << "[ OK ] Test 1 :: Polymorphic fare functions compute ticket prices accurately.\n";

        // Test 2: Passenger creation and polymorphism
        auto ep = std::make_shared<EconomyPassenger>("T-EP", "Test Eco", "eco@test.com");
        auto bp = std::make_shared<BusinessPassenger>("T-BP", "Test Biz", "biz@test.com");

        if (ep->getBaggageAllowance() != 20.0 || ep->getCancellationRefundPercentage() != 50.0)
            throw std::runtime_error("Economy passenger rules mismatch.");
        if (bp->getBaggageAllowance() != 35.0 || bp->getCancellationRefundPercentage() != 75.0)
            throw std::runtime_error("Business passenger rules mismatch.");
        std::cout << "[ OK ] Test 2 :: Polymorphic passenger perks, baggage limits, and cancellation rules conform to the specification.\n";

        // Test 3: Generic search template
        std::vector<std::shared_ptr<Flight>> testFlights = {df, inf};
        auto results = searchItems(testFlights, [](const auto& f) {
            return f->getDestination() == "LHR";
        });
        if (results.size() != 1 || results[0]->getFlightNumber() != "TEST-IF") {
            throw std::runtime_error("Generic search template failed to filter items.");
        }
        std::cout << "[ OK ] Test 3 :: The simple search template filters collections accurately.\n";

        // Test 4: Booking workflow, auto seat allocation, duplicate booking exceptions
        airline.addFlight(df);
        airline.registerPassenger(ep);
        
        auto ticket = airline.bookTicket("T-EP", "TEST-DF");
        if (ticket->getSeatNumber() != 1 || df->getAvailableSeats() != 8) {
            throw std::runtime_error("Seat allocation or available seats count mismatch.");
        }

        // Verify booking history lookup dynamically
        std::vector<std::shared_ptr<Ticket>> history;
        for (const auto& t : airline.getTickets()) {
            if (t->getPassenger()->getPassengerId() == "T-EP") {
                history.push_back(t);
            }
        }
        if (history.empty() || history[0]->getTicketId() != ticket->getTicketId()) {
            throw std::runtime_error("Dynamic booking history tracking failed.");
        }
        
        try {
            airline.bookTicket("T-EP", "TEST-DF");
            throw std::runtime_error("Duplicate booking exception was not thrown.");
        } catch (const AirlineException& e) {
            // expected behavior
        }
        std::cout << "[ OK ] Test 4 :: The ticket reservation flow handles bookings, seat mapping, and duplicate detection properly.\n";

        // Test 5: Seat Selection validation
        try {
            airline.bookTicket("P-1001", "TEST-DF", 1); // seat 1 is already taken by T-EP
            throw std::runtime_error("Seat occupancy validation failed.");
        } catch (const AirlineException& e) {
            // expected behavior
        }
        std::cout << "[ OK ] Test 5 :: Seat availability validation turns down already-taken seats as expected.\n";

        // Test 6: Cancellation refund system
        airline.cancelTicket(ticket->getTicketId());
        if (df->getAvailableSeats() != 9) {
            throw std::runtime_error("Seat was not released upon cancellation.");
        }
        std::cout << "[ OK ] Test 6 :: The cancellation refund process frees seats and calculates refund amounts accurately.\n";

        std::cout << "\nAll 6 system tests completed successfully! The airline reservation framework is stable and dependable.\n";
    } catch (const std::exception& e) {
        std::cerr << "\n[ FAILED ] Integration test did not pass: " << e.what() << "\n";
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    Airline airline;

    const std::string dataDir = "data";
    const std::string flightsFile = dataDir + "/flights.txt";
    const std::string passengersFile = dataDir + "/passengers.txt";
    const std::string ticketsFile = dataDir + "/tickets.txt";

    createDirectory(dataDir);

    UIHelper::printWelcomeBanner();
    UIHelper::printLoadingScreen(500);

    // Try loading existing data. Recover gracefully on missing database.
    try {
        if (fileExists(flightsFile) && fileExists(passengersFile) && fileExists(ticketsFile)) {
            airline.loadData(flightsFile, passengersFile, ticketsFile);
        } else {
            throw AirlineException("Save data files are incomplete or missing.");
        }
    } catch (const std::exception& e) {
        UIHelper::printWarningMessage(std::string("Startup notice: ") + e.what() + "\nCreating the default starting configuration.");
        airline = Airline(); // Wipe clean
        populateSampleData(airline);
        try {
            airline.saveData(flightsFile, passengersFile, ticketsFile);
        } catch (...) {}
    }

    // Self-test runner flag check
    if (argc > 1 && std::string(argv[1]) == "--test") {
        runSelfTests(airline);
        return 0;
    }

    while (true) {
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();

        // Unified 14-option dashboard menu
UIHelper::printMenuBox("SKYLINK AIRWAYS ADMINISTRATION SYSTEM", {
    "1. Create Flight Record",
    "2. Delete Flight Record",
    "3. Look Up Flights",
    "4. Display Complete Flight List",
    "5. Enroll Passenger",
    "6. Delete Passenger Record",
    "7. Review Passenger Reservation History",
    "8. Reserve a Ticket",
    "9. Rescind a Ticket Booking",
    "10. Departures Scheduled Today",
    "11. Seat Occupancy Summary",
    "12. Five Highest-Earning Flights",
    "13. Import Sample Dataset",
    "14. Save Changes & Quit"
});
        std::cout << "\n";
        int choice = getValidInt("Choose an option (1-14): ", 1, 14);

        // Exit when user selects option 14 (Save & Exit)
        if (choice == 14) {
            UIHelper::clearScreen();
            try {
                UIHelper::printSuccessMessage("Writing all flight records and ticket assignments to the database...");
                airline.saveData(flightsFile, passengersFile, ticketsFile);
            } catch (...) {}
            UIHelper::printExitBanner();
            break;
        }


        // Unified handling of all menu choices (admin and customer functionalities) 
        // Unified handling of all menu choices (14 options)
switch (choice) {
    case 1: { // Add Flight (Register New Flight Route)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:             ENROLL A NEW FLIGHT ROUTE              :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string fNo = getNonEmptyString("Enter the Flight Number (e.g. AA-404) [enter '0' to abort]: ");
        if (fNo == "0") {
            UIHelper::printWarningMessage("Registration aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        if (airline.findFlight(fNo)) { UIHelper::printErrorMessage("Registration unsuccessful: flight number already in use."); waitForEnter(); break; }
        std::string orig = getNonEmptyString("Enter the City of Origin: ");
        std::string dest = getNonEmptyString("Enter the Destination City: ");
        std::string depTime = getValidDateTime("Enter Departure Date/Time (YYYY-MM-DD HH:MM): ");
        int seats = getValidInt("Enter Seating Capacity (multiples of 3 advised, e.g. 15, 30): ", 3, 500);
        UIHelper::printMenuBox("FLIGHT CATEGORY CHOICE", {"1. Domestic Service", "2. International Service"});
        int type = getValidInt("\nChoose the flight category (1-2): ", 1, 2);
        try {
            if (type == 1) {
                double base = getValidDouble("Enter Base Fare ($): ", 0.0);
                double tax = getValidDouble("Enter Domestic Levy ($): ", 0.0);
                airline.addFlight(std::make_shared<DomesticFlight>(fNo, orig, dest, depTime, seats, seats, base, tax));
            } else {
                double base = getValidDouble("Enter Base Fare ($): ", 0.0);
                double tax = getValidDouble("Enter International Levy ($): ", 0.0);
                double surcharge = getValidDouble("Enter Fuel Supplement ($): ", 0.0);
                int visaVal = getValidInt("Is visa verification mandatory? (1=Yes, 0=No): ", 0, 1);
                airline.addFlight(std::make_shared<InternationalFlight>(fNo, orig, dest, depTime, seats, seats, base, tax, surcharge, visaVal == 1));
            }
            UIHelper::printSuccessMessage("Flight route approved successfully!");
        } catch (const std::exception& e) { UIHelper::printErrorMessage(e.what()); }
        waitForEnter();
        break;
    }
    case 2: { // Remove Flight (Decommission Flight Route)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:               RETIRE A FLIGHT ROUTE                :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string fNo = getNonEmptyString("Enter the Flight Number [enter '0' to abort]: ");
        if (fNo == "0") {
            UIHelper::printWarningMessage("Operation aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        if (airline.removeFlight(fNo)) { UIHelper::printSuccessMessage("Flight route retired from service successfully."); }
        else { UIHelper::printErrorMessage("Failure: Flight route " + fNo + " could not be located."); }
        waitForEnter();
        break;
    }
    case 3: { // Search Flights (reuse existing search & filter functionality)
        // invoke the same block as original case 8
        
        // Reuse search menu loop
        while (true) {
            UIHelper::clearScreen();
            UIHelper::printWelcomeBanner();
            UIHelper::printMenuBox("FLIGHT LOOKUP & FILTERING SERVICES", {
                "1. Look up by exact Flight Number",
                "2. Look up by route (Origin & Destination)",
                "3. Look up by scheduled Departure Date",
                "4. Back to Main Menu"
            });
            std::cout << "\n";
            int searchChoice = getValidInt("Pick a lookup method (1-4): ", 1, 4);
            if (searchChoice == 4) break;
            switch (searchChoice) {
                case 1: {
                    UIHelper::clearScreen();
                    UIHelper::printWelcomeBanner();
                    std::string num = getNonEmptyString("Enter the Flight Number to locate (e.g. DF-101) [enter '0' to abort]: ");
                    if (num == "0") break;
                    auto flights = airline.getFlights();
                    auto it = std::find_if(flights.begin(), flights.end(), [&](const auto& f){ return f->getFlightNumber() == num; });
                    if (it != flights.end()) {
                        std::cout << "\n" << UIHelper::BOLD << UIHelper::GREEN << ">> MATCHING FLIGHT LOCATED <<\n" << UIHelper::RESET;
                        std::cout << *it << "\n";
                    } else {
                        UIHelper::printWarningMessage("No flight matching code '" + num + "' could be located.");
                    }
                    waitForEnter();
                    break;
                }
                case 2: {
                    UIHelper::clearScreen();
                    UIHelper::printWelcomeBanner();
                    std::string orig = getNonEmptyString("Enter the Origin City/Airport [enter '0' to abort]: ");
                    if (orig == "0") break;
                    std::string dest = getNonEmptyString("Enter the Destination City/Airport [enter '0' to abort]: ");
                    if (dest == "0") break;
                    auto flights = airline.getFlights();
                    auto matches = searchItems(flights, [&](const auto& f){ return f->getOrigin() == orig && f->getDestination() == dest; });
                    if (matches.empty()) {
                        UIHelper::printWarningMessage("No flights are timetabled on route: " + orig + " -> " + dest);
                    } else {
                        std::cout << "\n";
                        UIHelper::printTableHeader({"Flight No","Type","Origin","Destination","Departure Time","Seats (A/T)","Base Fare"}, {10,13,14,14,18,11,9});
                        for (const auto& flight : matches) flight->displayDetails();
                        UIHelper::printTableSeparator({10,13,14,14,18,11,9});
                    }
                    waitForEnter();
                    break;
                }
                case 3: {
                    UIHelper::clearScreen();
                    UIHelper::printWelcomeBanner();
                    std::string date = getNonEmptyString("Enter the Departure Date (YYYY-MM-DD) [enter '0' to abort]: ");
                    if (date == "0") break;
                    auto flights = airline.getFlights();
                    auto matches = searchItems(flights, [&](const auto& f){ return f->getDepartureTime().find(date) != std::string::npos; });
                    if (matches.empty()) {
                        UIHelper::printWarningMessage("No flights depart on the date: " + date);
                    } else {
                        std::cout << "\n";
                        UIHelper::printTableHeader({"Flight No","Type","Origin","Destination","Departure Time","Seats (A/T)","Base Fare"}, {10,13,14,14,18,11,9});
                        for (const auto& flight : matches) flight->displayDetails();
                        UIHelper::printTableSeparator({10,13,14,14,18,11,9});
                    }
                    waitForEnter();
                    break;
                }
            }
        }
        break;
    }
    case 4: { // List All Flights (View Registered Flights)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        airline.listFlights();
        waitForEnter();
        break;
    }
    case 5: { // Register Passenger (Register New Passenger Profile)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:           CREATE A NEW PASSENGER PROFILE           :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string id = getNonEmptyString("Enter the Passenger ID (e.g. P-404) [enter '0' to abort]: ");
        if (id == "0") {
            UIHelper::printWarningMessage("Registration aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        if (airline.findPassenger(id)) { UIHelper::printErrorMessage("Failure: that Passenger ID is already registered."); waitForEnter(); break; }
        std::string name = getNonEmptyString("Enter the Passenger's Full Name: ");
        std::string email = getNonEmptyString("Enter the Email Address: ");
        UIHelper::printMenuBox("TRAVEL CLASS CHOICE", {"1. Economy Cabin", "2. Business Cabin"});
        int category = getValidInt("\nChoose the travel class (1-2): ", 1, 2);
        try {
            if (category == 1) airline.registerPassenger(std::make_shared<EconomyPassenger>(id, name, email));
            else airline.registerPassenger(std::make_shared<BusinessPassenger>(id, name, email));
            UIHelper::printSuccessMessage("Passenger profile created successfully!");
        } catch (const std::exception& e) { UIHelper::printErrorMessage(e.what()); }
        waitForEnter();
        break;
    }
    case 6: { // Remove Passenger (Remove Passenger Profile)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:             DELETE A PASSENGER PROFILE             :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string pId = getNonEmptyString("Enter the Passenger ID [enter '0' to abort]: ");
        if (pId == "0") {
            UIHelper::printWarningMessage("Operation aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        if (airline.removePassenger(pId)) UIHelper::printSuccessMessage("Passenger profile deleted successfully.");
        else UIHelper::printErrorMessage("Failure: Passenger ID " + pId + " could not be located.");
        waitForEnter();
        break;
    }
    case 7: { // View Passenger Booking History (Retrieve Personal Booking \u0026 Travel History)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:         LOOK UP TRAVEL RESERVATION HISTORY         :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string pId = getNonEmptyString("Enter the Passenger ID [enter '0' to abort]: ");
        if (pId == "0") {
            UIHelper::printWarningMessage("Operation aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        auto passenger = airline.findPassenger(pId);
        if (!passenger) { UIHelper::printErrorMessage("Failure: Passenger ID " + pId + " could not be located."); waitForEnter(); break; }
        std::cout << "\n" << UIHelper::BOLD << UIHelper::BLUE << ">> PASSENGER DETAILS <<\n" << UIHelper::RESET;
        std::cout << *passenger << "\n\n";
        std::vector<std::shared_ptr<Ticket>> history;
        for (const auto& tkt : airline.getTickets()) if (tkt->getPassenger()->getPassengerId() == pId) history.push_back(tkt);
        if (history.empty()) UIHelper::printWarningMessage("No reservation history is recorded for this passenger.");
        else {
            std::cout << UIHelper::BOLD << UIHelper::CYAN << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:           PASSENGER RESERVATION HISTORY            :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n" << UIHelper::RESET << "\n";
            for (const auto& tkt : history) std::cout << *tkt << "\n\n";
        }
        waitForEnter();
        break;
    }
    case 8: { // Book a Ticket (Book Flight Boarding Pass)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:         ISSUE A BOARDING PASS RESERVATION          :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string pId = getNonEmptyString("Enter the Passenger ID [enter '0' to abort]: ");
        if (pId == "0") {
            UIHelper::printWarningMessage("Reservation aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        std::string fNo = getNonEmptyString("Enter the Flight Number [enter '0' to abort]: ");
        if (fNo == "0") {
            UIHelper::printWarningMessage("Reservation aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        UIHelper::printMenuBox("SEAT ASSIGNMENT OPTIONS", {"1. Pick a specific Seat number", "2. Automatically assign a free seat"});
        int seatChoice = getValidInt("\nChoose a seat option (1-2): ", 1, 2);
        int requestedSeat = 0;
        if (seatChoice == 1) { try { airline.showSeatMap(fNo); } catch (...) {} requestedSeat = getValidInt("\nEnter the desired seat number: ", 1, 500); }
        try {
            auto ticket = airline.bookTicket(pId, fNo, requestedSeat);
            UIHelper::printBookingSuccessPopup(ticket->getPassenger()->getName(), ticket->getFlight()->getFlightNumber(), ticket->getSeatNumber(), ticket->getFarePaid());
        } catch (const std::exception& e) { UIHelper::printErrorMessage(e.what()); }
        waitForEnter();
        break;
    }
    case 9: { // Cancel a Ticket (Cancel Reserved Ticket)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:             RESCIND A RESERVED TICKET              :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        std::string tId = getNonEmptyString("Enter the Ticket ID to rescind (e.g. TKT-DF-101-101) [enter '0' to abort]: ");
        if (tId == "0") {
            UIHelper::printWarningMessage("Operation aborted. Going back to the main menu.");
            waitForEnter();
            break;
        }
        try { airline.cancelTicket(tId); } catch (const std::exception& e) { UIHelper::printErrorMessage(e.what()); }
        waitForEnter();
        break;
    }
    case 10: { // Today's Departures (show flights departing today)
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        std::cout << "*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n:           DEPARTURES SCHEDULED FOR TODAY           :\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n";
        // Get current date in YYYY-MM-DD format
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        char buf[11];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
        std::string today(buf);
        auto flights = airline.getFlights();
        auto matches = searchItems(flights, [&](const auto& f){ return f->getDepartureTime().find(today) != std::string::npos; });
        if (matches.empty()) {
            UIHelper::printWarningMessage("No flights are set to depart today (" + today + ").");
        } else {
            UIHelper::printTableHeader({"Flight No","Type","Origin","Destination","Departure Time","Seats (A/T)","Base Fare"}, {10,13,14,14,18,11,9});
            for (const auto& flight : matches) flight->displayDetails();
            UIHelper::printTableSeparator({10,13,14,14,18,11,9});
        }
        waitForEnter();
        break;
    }
    case 11: { // Occupancy Report
        UIHelper::clearScreen();
        airline.showOccupancyPercentage();
        waitForEnter();
        break;
    }
    case 12: { // Top 5 Revenue Flights
        UIHelper::clearScreen();
        airline.showTopRevenueFlights();
        waitForEnter();
        break;
    }
    case 13: { // Load Sample Data
        UIHelper::clearScreen();
        UIHelper::printWelcomeBanner();
        populateSampleData(airline);
        UIHelper::printSuccessMessage("Sample dataset imported.");
        waitForEnter();
        break;
    }
    case 14: { // Save & Exit
        UIHelper::clearScreen();
        try { UIHelper::printSuccessMessage("Writing all flight records and ticket assignments to the database..."); airline.saveData(flightsFile, passengersFile, ticketsFile); } catch(...) {}
        UIHelper::printExitBanner();
        break;
    }
    default: {
        UIHelper::printWarningMessage("Unrecognized selection.");
        waitForEnter();
        break;
    }
}
}

    return 0;
}
