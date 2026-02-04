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

    // Try environment override first (useful for GUI or manual overrides)
    const char* env_tshark = std::getenv("TSHARK_PATH");
    if (env_tshark) {
        sniffer.setTsharkPath(std::string(env_tshark));
        ui.log(std::string("Using TSHARK_PATH from environment: ") + env_tshark, "INFO");
    } else {
        // Auto-detect and inform user / GUI
        std::string found = Executor::findUtility("tshark");
        if (!found.empty()) {
            sniffer.setTsharkPath(found);
            ui.log(std::string("Detected tshark at: ") + found, "INFO");
        } else {
            ui.log("tshark not found. Start install scripts in /scripts or set TSHARK_PATH", "ERROR");
            // Do not exit here to allow GUI to continue and user to set path later.
        }
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