#pragma once

#include<string>

namespace atlas{
    void log_info(const std::string& message);
    void log_warn(const std::string& message);
    void log_error(const std::string& message);
}