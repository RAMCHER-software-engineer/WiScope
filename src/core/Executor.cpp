#include "core/Executor.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

std::string Executor::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

#include <unistd.h>

bool Executor::isInstalled(const std::string& utility) {
    // First try `command -v` which works in most shells and environments
    std::string checkCmd = "command -v " + utility + " >/dev/null 2>&1";
    if (system(checkCmd.c_str()) == 0) {
        return true;
    }

    // Fallback: check common installation directories (macOS / Homebrew, Linux)
    const std::string commonPaths[] = {"/opt/homebrew/bin/", "/usr/local/bin/", "/usr/bin/", "/bin/", "/usr/sbin/"};
    for (const auto& dir : commonPaths) {
        std::string full = dir + utility;
        if (access(full.c_str(), X_OK) == 0) {
            return true;
        }
    }

    return false;
}

std::string Executor::findUtility(const std::string& utility) {
    // Try `command -v` and capture output
    std::string cmd = "command -v " + utility + " 2>/dev/null";
    std::array<char, 256> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (pipe) {
        if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result = buffer.data();
            // strip newline
            while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) result.pop_back();
            if (!result.empty()) {
                return result;
            }
        }
    }

    // Fallback: check common paths
    const std::string commonPaths[] = {"/opt/homebrew/bin/", "/usr/local/bin/", "/usr/bin/", "/bin/", "/usr/sbin/"};
    for (const auto& dir : commonPaths) {
        std::string full = dir + utility;
        if (access(full.c_str(), X_OK) == 0) {
            return full;
        }
    }

    return std::string();
}

#include <sstream>

std::vector<std::string> Executor::listTsharkInterfaces(const std::string& tsharkPath) {
    std::vector<std::string> res;
    std::string tshark = tsharkPath.empty() ? findUtility("tshark") : tsharkPath;
    if (tshark.empty()) return res;

    std::string cmd = tshark + " -D 2>/dev/null";
    std::string output;
    try {
        output = exec(cmd.c_str());
    } catch (...) {
        return res;
    }

    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line)) {
        // trim
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
        if (!line.empty()) res.push_back(line);
    }
    return res;
}