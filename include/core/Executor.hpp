#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>

class Executor {
    public:
        static std::string exec(const char* cmd);

        static bool isInstalled(const std::string& utility);

        // Return full path to utility if found (searches PATH and common install dirs),
        // or empty string if not found. Useful for GUI to display or set explicit path.
        static std::string findUtility(const std::string& utility);

        // Return raw lines from `tshark -D` to enumerate interfaces (empty if tshark missing)
        static std::vector<std::string> listTsharkInterfaces(const std::string& tsharkPath = "");
};

#endif // EXECUTOR_HPP