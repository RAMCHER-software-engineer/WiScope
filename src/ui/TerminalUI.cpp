#include "ui/TerminalUI.hpp"
#include "core/Sniffer.hpp"
#include <iostream>
#include <iomanip>

TerminalUI::TerminalUI() {}

void TerminalUI::clearScreen() {
    std::cout << "\033[2J\033[H";
}

void TerminalUI::init() {
    clearScreen();
    drawHeader();
}

void TerminalUI::showMenu() {
    std::cout << "\n" << colorCayan << "[ SYSTEM MENU ]" << colorReset << std::endl;
    std::cout << "1. Start Scanning Networks" << std::endl;
    std::cout << "2. Local Network Audit (Nmap)" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << ">> ";
}

void TerminalUI::drawHeader() {
    std::cout << colorCayan << "========================================" << std::endl; // Исправлено
    std::cout << "          WiScope v1.0 - Alpha          " << std::endl;
    std::cout << "========================================" << colorReset << std::endl;
}

void TerminalUI::log(const std::string& message, const std::string& type) {
    std::string prefix = "[" + type + "] ";
    if (type == "ERROR") std::cout << colorRed << prefix << message << colorReset << std::endl;
    else if (type == "SUCCESS") std::cout << colorGreen << prefix << message << colorReset << std::endl;
    else std::cout << colorCayan << prefix << message << colorReset << std::endl; // Исправлено
}

void TerminalUI::displayNetworks(const std::vector<WiFiNetwork>& networks) {
    std::cout << "\n" << std::left << std::setw(20) << "SSID" 
              << std::setw(18) << "BSSID" 
              << "Signal (dBm)" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (const auto& net : networks) {
        std::string signalColor = colorGreen;
        if (net.signalStrength < -70) signalColor = colorRed;
        else if (net.signalStrength < -50) signalColor = "\033[33m"; 

        std::cout << std::left << std::setw(20) << (net.ssid.empty() ? "<Hidden>" : net.ssid)
                  << std::setw(18) << net.bssid
                  << signalColor << net.signalStrength << " dBm" << colorReset << std::endl;
    }
}