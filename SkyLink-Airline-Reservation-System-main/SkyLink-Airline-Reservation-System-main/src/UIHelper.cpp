#include "UIHelper.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
static void sleepMs(int ms) {
    Sleep(ms);
}
#else
#include <unistd.h>
static void sleepMs(int ms) {
    usleep(ms * 1000);
}
#endif

// ANSI color sequences definition
const std::string UIHelper::RESET   = "\033[0m";
const std::string UIHelper::BOLD    = "\033[1m";
const std::string UIHelper::DIM     = "\033[2m";
const std::string UIHelper::RED     = "\033[1;31m";
const std::string UIHelper::GREEN   = "\033[1;32m";
const std::string UIHelper::YELLOW  = "\033[1;33m";
const std::string UIHelper::BLUE    = "\033[1;34m";
const std::string UIHelper::MAGENTA = "\033[1;35m";
const std::string UIHelper::CYAN    = "\033[1;36m";
const std::string UIHelper::WHITE   = "\033[1;37m";

void UIHelper::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void UIHelper::printHorizontalLine(int width, char symbol) {
    std::cout << "+" << std::string(width - 2, symbol) << "+\n";
}

void UIHelper::printBoxTop(int width, char symbol) {
    std::cout << "+" << std::string(width - 2, symbol) << "+\n";
}

void UIHelper::printBoxBottom(int width, char symbol) {
    std::cout << "+" << std::string(width - 2, symbol) << "+\n";
}

void UIHelper::printCenteredText(const std::string& text, int width, const std::string& color) {
    int totalPadding = width - 2 - static_cast<int>(text.length());
    if (totalPadding < 0) totalPadding = 0;
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;

    std::cout << "|";
    if (!color.empty()) std::cout << color;
    std::cout << std::string(leftPadding, ' ') << text << std::string(rightPadding, ' ');
    if (!color.empty()) std::cout << RESET;
    std::cout << "|\n";
}

void UIHelper::printWelcomeBanner() {
    clearScreen();
    int width = 70;
    std::cout << BOLD << CYAN;
    printHorizontalLine(width, '=');
    printCenteredText("WELCOME TO SKYLINK AIRWAYS", width, BOLD + CYAN);
    printCenteredText("Flight Reservation & Fleet Management Control System", width, DIM);
    printCenteredText("Version 2.0 (Premium OOP Edition)", width, YELLOW);
    printHorizontalLine(width, '=');
    std::cout << RESET << "\n";
}

void UIHelper::printLoadingScreen(int durationMs) {
    std::cout << BOLD << CYAN << "Loading Airline Database...\n" << RESET;
    std::cout << "[";
    int progressSteps = 10;
    int sleepInterval = durationMs / progressSteps;
    for (int i = 0; i < progressSteps; ++i) {
        std::cout << "#" << std::flush;
        sleepMs(sleepInterval);
    }
    std::cout << "] 100%\n\n";
}

void UIHelper::printExitBanner() {
    std::cout << BOLD << CYAN
              << "+================================================================================+\n"
              << "|                  THANK YOU FOR USING SKYLINK AIRWAYS SYSTEM                    |\n"
              << "+================================================================================+\n"
              << RESET << "\n";
}

void UIHelper::printFooter() {
    int width = 70;
    std::cout << BOLD << BLUE;
    printHorizontalLine(width, '=');
    printCenteredText("Designed by SkyLink Development Team", width, DIM);
    printCenteredText("Viva Exam Mode: Fully OOP & C++17 Compliant", width, YELLOW);
    printHorizontalLine(width, '=');
    std::cout << RESET << "\n";
}

void UIHelper::printMenuBox(const std::string& title, const std::vector<std::string>& options) {
    int width = 54;
    std::cout << BOLD << CYAN;
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    printCenteredText(title, width, BOLD + MAGENTA);
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    std::cout << RESET;

    for (const auto& opt : options) {
        std::string line = "  " + opt;
        int padding = width - 2 - static_cast<int>(line.length());
        if (padding < 0) padding = 0;
        std::cout << "| " << BOLD << opt << std::string(padding, ' ') << "|\n";
    }

    std::cout << BOLD << CYAN;
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    std::cout << RESET;
}

void UIHelper::printSuccessMessage(const std::string& msg) {
    int width = 60;
    std::cout << "\n" << BOLD << GREEN;
    printHorizontalLine(width, '*');
    printCenteredText("OPERATION SUCCESSFUL", width, BOLD + GREEN);
    printHorizontalLine(width, '-');
    printCenteredText(msg, width, RESET);
    printHorizontalLine(width, '*');
    std::cout << RESET << "\n";
}

void UIHelper::printErrorMessage(const std::string& msg) {
    int width = 60;
    std::cout << "\n" << BOLD << RED;
    printHorizontalLine(width, '*');
    printCenteredText("ERROR DETECTED", width, BOLD + RED);
    printHorizontalLine(width, '-');
    printCenteredText(msg, width, RESET);
    printHorizontalLine(width, '*');
    std::cout << RESET << "\n";
}

void UIHelper::printWarningMessage(const std::string& msg) {
    int width = 60;
    std::cout << "\n" << BOLD << YELLOW;
    printHorizontalLine(width, '*');
    printCenteredText("WARNING NOTICE", width, BOLD + YELLOW);
    printHorizontalLine(width, '-');
    printCenteredText(msg, width, RESET);
    printHorizontalLine(width, '*');
    std::cout << RESET << "\n";
}

void UIHelper::printTableHeader(const std::vector<std::string>& headers, const std::vector<int>& widths) {
    // Top boundary
    std::cout << "+";
    for (size_t i = 0; i < widths.size(); ++i) {
        std::cout << std::string(widths[i] + 2, '-');
        if (i < widths.size() - 1) std::cout << "+";
    }
    std::cout << "+\n";

    // Header cells
    std::cout << "|";
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << " " << BOLD << CYAN << std::left << std::setw(widths[i]) << headers[i] << RESET << " |";
    }
    std::cout << "\n";

    // Separator line
    printTableSeparator(widths);
}

void UIHelper::printTableRow(const std::vector<std::string>& cells, const std::vector<int>& widths, const std::string& textColor) {
    std::cout << "|";
    for (size_t i = 0; i < cells.size(); ++i) {
        std::cout << " ";
        if (!textColor.empty()) std::cout << textColor;
        std::cout << std::left << std::setw(widths[i]) << cells[i] << RESET << " |";
    }
    std::cout << "\n";
}

void UIHelper::printTableSeparator(const std::vector<int>& widths) {
    std::cout << "+";
    for (size_t i = 0; i < widths.size(); ++i) {
        std::cout << std::string(widths[i] + 2, '-');
        if (i < widths.size() - 1) std::cout << "+";
    }
    std::cout << "+\n";
}

void UIHelper::printBookingSuccessPopup(const std::string& passengerName, const std::string& flightNo, int seatNo, double fare) {
    int width = 50;
    std::cout << "\n" << BOLD << GREEN;
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    printCenteredText("BOARDING TICKET RESERVED", width, BOLD + GREEN);
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    std::cout << RESET;

    std::vector<std::pair<std::string, std::string>> fields = {
        {"Passenger", passengerName},
        {"Flight No", flightNo},
        {"Seat allocated", "Seat #" + std::to_string(seatNo)},
        {"Fare collected", "$" + std::to_string(static_cast<int>(fare)) + ".00"}
    };

    for (const auto& field : fields) {
        std::string content = "  " + field.first + " : " + field.second;
        int padding = width - 2 - static_cast<int>(content.length());
        if (padding < 0) padding = 0;
        std::cout << "| " << BOLD << field.first << RESET << ": " << std::left << std::setw(width - 6 - static_cast<int>(field.first.length())) << field.second << " |\n";
    }

    std::cout << BOLD << GREEN;
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    std::cout << RESET << "\n";
}

void UIHelper::printCancellationSuccessPopup(const std::string& ticketId, const std::string& name, double refundPct, double refundAmount) {
    int width = 50;
    std::cout << "\n" << BOLD << RED;
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    printCenteredText("TICKET VOIDED & REFUNDED", width, BOLD + RED);
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    std::cout << RESET;

    std::vector<std::pair<std::string, std::string>> fields = {
        {"Ticket ID", ticketId},
        {"Passenger", name},
        {"Refund Settle", std::to_string(static_cast<int>(refundPct)) + "% Refund processed"},
        {"Refund Amount", "$" + std::to_string(static_cast<int>(refundAmount)) + ".00"}
    };

    for (const auto& field : fields) {
        std::string content = "  " + field.first + " : " + field.second;
        int padding = width - 2 - static_cast<int>(content.length());
        if (padding < 0) padding = 0;
        std::cout << "| " << BOLD << field.first << RESET << ": " << std::left << std::setw(width - 6 - static_cast<int>(field.first.length())) << field.second << " |\n";
    }

    std::cout << BOLD << RED;
    std::cout << "+" << std::string(width - 2, '=') << "+\n";
    std::cout << RESET << "\n";
}
