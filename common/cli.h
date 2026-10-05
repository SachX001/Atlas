#pragma once

#include<string>

#include "config.h"

namespace atlas{
    struct ParseResult {
        bool success;
        Config config;
        std::string error_message;
    };

    ParseResult parse_arguments(int argc, char* argv[]);

}