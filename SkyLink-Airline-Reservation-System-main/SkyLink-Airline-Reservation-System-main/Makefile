# SkyLink Airline Reservation & Flight Management System Makefile
# Configured for g++ C++17 compilation on Windows and general environments

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude -static

# Source files list (excluding deleted CharterFlight and FirstClassPassenger files)
SRCS = src/Flight.cpp \
       src/DomesticFlight.cpp \
       src/InternationalFlight.cpp \
       src/Passenger.cpp \
       src/EconomyPassenger.cpp \
       src/BusinessPassenger.cpp \
       src/Ticket.cpp \
       src/Airline.cpp \
       src/UIHelper.cpp \
       main.cpp

# Target executable name
TARGET = SkyLinkSystem

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	@echo Cleaning up binary file...
	@if exist $(TARGET).exe del /F /Q $(TARGET).exe
	@if exist $(TARGET) del /F /Q $(TARGET)
