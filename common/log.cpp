#include "log.h"

#include <iostream>
#include <string>

namespace atlas {
    void log_info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }

    void log_warn(const std::string& message) {
        std::cout << "[WARN] " << message << std::endl;
    }

    void log_error(const std::string& message) {
        std::cout << "[ERROR] " << message << std::endl;
    }
}