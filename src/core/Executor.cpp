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

bool Executor::isInstalled(const std::string& utility) {
    std::string checkCmd = "commnand -v " + utility + " 2>/dev/null";
    return (system(checkCmd.c_str()) == 0);
}