#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "check_root.h"
#include "ui/TerminalUI.hpp"
#include "core/Sniffer.hpp"
#include "core/Executor.hpp"

int main() {
    TerminalUI ui;
    Sniffer sniffer;
    
    ui.init();
    ui.log("Start system WiScope", "INFO");

    ui.log("Check privilege (ASM)...", "INFO");
    if (check_root_asm() != 1) {
        ui.log("ERROR: Required ROOT rights (sudo).", "ERROR");
        return 1;
    }
    ui.log("Access confirmed!", "SUCCESS");

    if (!Executor::isInstalled("tshark")) {
        ui.log("tshark not found. Start install scripts to /scripts", "ERROR");
        return 1;
    }
    bool running = true;
    while (running) {
        ui.showMenu();
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                ui.clearScreen();
                ui.log("Start scan (5 second)...", "INFO");
                sniffer.startScan("en0"); 
                
                auto nets = sniffer.getDetectedNetworks();
                ui.displayNetworks(nets);
                
                std::cout << "\nPress Enter to return to menu...";
                std::cin.ignore(1000, '\n');
                std::cin.get();
                ui.clearScreen();
                break;
            }
            case 2:
                ui.log("Function audit nmap", "INFO");
                break;
            case 3:
                running = false;
                ui.log("Exit system...", "INFO");
                break;
            default:
                ui.log("Invalid choice, try again.", "ERROR");
        }
    }

    return 0;
}