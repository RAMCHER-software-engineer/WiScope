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
        Sniffer() : isRunning(false), iface("en0") {}

        // Start/stop scanning. For GUI, set interface/path before calling startScan().
        void startScan(const std::string& interface = "");
        void stopScan();
        std::vector<WiFiNetwork> getDetectedNetworks() const;

        // GUI-friendly setters/getters
        void setTsharkPath(const std::string& path) { tsharkPath = path; }
        std::string getTsharkPath() const { return tsharkPath; }

        void setInterface(const std::string& interface) { iface = interface; }
        std::string getInterface() const { return iface; }

        // Return raw interface lines (as returned by `tshark -D`) for GUI to show and let user pick
        std::vector<std::string> listInterfaces() const;

    private:
        std::atomic<bool> isRunning;
        std::vector<WiFiNetwork> discovered;
        std::string tsharkPath; // explicit path to tshark if user supplied
        std::string iface;
        void parseTsharkOutput(const std::string& rawLine);
};

#endif // SNIFFER_HPP