#include "core/Sniffer.hpp"
#include "core/Executor.hpp"
#include <iostream>

void Sniffer::startScan(const std::string& interface) {
    if (!Executor::isInstalled("tshark")) {
        std::cerr << "[!] tshark not installed or not accessible" << std::endl;
        return;
    }

    isRunning = true;
    std::string cmd = "tshark -i " + interface + " -a duration:5 -T fields -e wlan.ssid -e wlan_radio.signal_dbm";
    
    std::cout << "[*] Starting scan on interface " << interface << "..." << std::endl;
    
    std::string output = Executor::exec(cmd.c_str());
    std::cout << output << std::endl;
    
    isRunning = false;
}

std::vector<WiFiNetwork> Sniffer::getDetectedNetworks() const {
    return discovered;
}

void Sniffer::stopScan() {
    isRunning = false;
}