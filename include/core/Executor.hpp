#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>

class Executor {
    public:
        static std::string exec(const char* cmd);

        static bool isInstalled(const std::string& utility);
};

#endif // EXECUTOR_HPP