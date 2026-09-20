#ifndef UI_HELPER_H
#define UI_HELPER_H

#include <string>
#include <vector>

class UIHelper {
public:
    // Color constants (ANSI escape sequences)
    static const std::string RESET;
    static const std::string BOLD;
    static const std::string DIM;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;

    // Formatting utilities
    static void clearScreen();
    static void printHorizontalLine(int width, char symbol = '-');
    static void printBoxTop(int width, char symbol = '-');
    static void printBoxBottom(int width, char symbol = '-');
    static void printCenteredText(const std::string& text, int width, const std::string& color = "");
    
    // Core layouts & banners
    static void printWelcomeBanner();
    static void printLoadingScreen(int durationMs = 1500);
    static void printExitBanner();
    static void printFooter();
    
    // Dialogs & Popups
    static void printMenuBox(const std::string& title, const std::vector<std::string>& options);
    static void printSuccessMessage(const std::string& msg);
    static void printErrorMessage(const std::string& msg);
    static void printWarningMessage(const std::string& msg);
    
    // Table components
    static void printTableHeader(const std::vector<std::string>& headers, const std::vector<int>& widths);
    static void printTableRow(const std::vector<std::string>& cells, const std::vector<int>& widths, const std::string& textColor = "");
    static void printTableSeparator(const std::vector<int>& widths);

    // Dynamic Popups
    static void printBookingSuccessPopup(const std::string& passengerName, const std::string& flightNo, int seatNo, double fare);
    static void printCancellationSuccessPopup(const std::string& ticketId, const std::string& name, double refundPct, double refundAmount);
};

#endif // UI_HELPER_H
