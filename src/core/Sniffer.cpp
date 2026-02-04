#include "core/Sniffer.hpp"
#include "core/Executor.hpp"
#include <iostream>

void Sniffer::startScan(const std::string& interface) {
    // decide interface
    std::string useInterface = interface.empty() ? iface : interface;

    // determine path to tshark (explicit path overrides detection)
    std::string tshark = !tsharkPath.empty() ? tsharkPath : Executor::findUtility("tshark");
    if (tshark.empty()) {
        std::cerr << "[!] tshark not installed or not accessible. Set TSHARK_PATH or install tshark." << std::endl;
        return;
    }

    isRunning = true;
    std::string cmd = tshark + std::string(" -i ") + useInterface + " -l -a duration:5 -T fields -e wlan.ssid -e wlan_radio.signal_dbm";
    
    std::cout << "[*] Starting scan on interface " << useInterface << " using: " << tshark << " ..." << std::endl;
    
    std::string output = Executor::exec(cmd.c_str());
    std::cout << output << std::endl;
    
    isRunning = false;
}

std::vector<std::string> Sniffer::listInterfaces() const {
    std::string path = !tsharkPath.empty() ? tsharkPath : Executor::findUtility("tshark");
    return Executor::listTsharkInterfaces(path);
}

std::vector<WiFiNetwork> Sniffer::getDetectedNetworks() const {
    return discovered;
}

void Sniffer::stopScan() {
    isRunning = false;
}