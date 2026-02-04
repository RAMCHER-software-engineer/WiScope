#ifndef TERMINALUI_HPP
#define TERMINALUI_HPP

#include <string>
#include <vector>
#include "core/Sniffer.hpp"

class TerminalUI {
    public:
        TerminalUI();
        ~TerminalUI() = default;

        void init();
        void showMenu();
        void displayNetworks(const std::vector<WiFiNetwork>& networks);
        void log(const std::string& message, const std::string& level = "INFO");
        void clearScreen();

    private:
        void drawHeader();
        void drawFooter();

        const std::string colorReset = "\033[0m";
        const std::string colorRed = "\033[31m";
        const std::string colorGreen = "\033[32m";
        const std::string colorCayan = "\033[36m";
        
};

#endif // TERMINALUI_HPP