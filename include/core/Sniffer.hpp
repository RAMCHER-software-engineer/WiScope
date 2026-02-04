#ifndef SNIFFER_HPP
#define SNIFFER_HPP

#include <string>
#include <vector>
#include <atomic>

struct WiFiNetwork {
    std::string ssid;
    std::string bssid;
    int signalStrength;
    std::string channel;
};

class Sniffer {
    public:
        Sniffer() : isRunning(false) {}

        void startScan(const std::string& interface);
        void stopScan();
        std::vector<WiFiNetwork> getDetectedNetworks() const;

    private:
        std::atomic<bool> isRunning;
        std::vector<WiFiNetwork> discovered;
        void parseTsharkOutput(const std::string& rawLine);
};

#endif 