# 🌟 SkyLink Airline Reservation System

**A pure OOP C++17 console application** for university coursework, featuring a unified **14‑option management menu** without any authentication screens.

---

## 📂 Project Structure
```
SkyLink-Airline-Reservation-System/
│
├── include/                 # Header Files (.h)
│   ├── Airline.h
│   ├── Flight.h
│   ├── DomesticFlight.h
│   ├── InternationalFlight.h
│   ├── Passenger.h
│   ├── EconomyPassenger.h
│   ├── BusinessPassenger.h
│   ├── Ticket.h
│   ├── Exceptions.h
│   └── SearchTemplate.h
│
├── src/                     # Source Files (.cpp)
│   ├── Airline.cpp
│   ├── Flight.cpp
│   ├── DomesticFlight.cpp
│   ├── InternationalFlight.cpp
│   ├── Passenger.cpp
│   ├── EconomyPassenger.cpp
│   ├── BusinessPassenger.cpp
│   └── Ticket.cpp
│
├── data/                    # Persistent storage (text files)
│   ├── flights.txt
│   ├── passengers.txt
│   └── tickets.txt
│
├── main.cpp                 # Entry point & menu driver
├── Makefile                 # Build script (includes -O2 optimisation)
├── VIVA_NOTES.md            # Viva preparation guide & UML diagram
└── README.md                # This documentation
```

---

## 🎨 Updated UI Highlights
- **Teal‑colored banner** on startup (`UIHelper::printWelcomeBanner`).
- **Consistent menu boxes** with colored titles and clean separators.
- **Success / Error / Warning pop‑ups** using ANSI colour codes for instant visual feedback.
- **Loading animation** with progress bar during data import.

---

## 🛠️ Compilation & Execution
The project targets **C++17** (or higher) and uses the `-O2` optimisation flag.

### 1️⃣ Build the project (Windows PowerShell or CMD)
```powershell
make clean && make
```
*If `make` is not on your PATH, use the MinGW wrapper:*
```powershell
mingw32-make clean && mingw32-make
```

### 2️⃣ Run the application
```powershell
.\\SkyLinkSystem.exe   # PowerShell / CMD
# or, from a Bash‑like shell
./SkyLinkSystem.exe
```
You will be greeted by the colourful 14‑option dashboard, with a **"Return to Main Menu"** option inside the Search submenu.

---

## 📤 Push the Final Code to GitHub
After confirming everything works, commit and push the changes:
```powershell
git add .
git commit -m "Refresh UI, update README, polish code style"
git push origin main
```
Repository URL:
```
https://github.com/khabsarali/SkyLink-Airline-Reservation-System
```

---

## 🚀 Key Features
- Unified 14‑option console menu (no auth screens).
- Polymorphic flight pricing and passenger benefits.
- Automatic seat allocation with optional manual selection.
- Persistence via simple flat‑file storage.
- Reports: today's departures, occupancy, top‑5 revenue flights, monthly revenue.
- Generic search template for filtering collections.

---

## ⚠️ Known Limitations
- Uses plain text files for data persistence.
- All operations run synchronously on a single thread.
- No graphical UI – console‑only.

---

*Feel free to explore the code, run the self‑tests (`./SkyLinkSystem.exe --test`), and extend the system as needed.*

SkyLink is a **pure OOP C++17 console application** built for a university assignment. All authentication and role‑based screens have been removed per the project specification – the program launches directly into the unified **14‑option management menu**.

