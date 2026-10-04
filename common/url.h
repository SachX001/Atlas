#pragma once

#include <string>
namespace atlas {

    struct Url{
        std::string raw;
        std::string normalized;

        std::string scheme;
        std::string host;
        std::string path;

        int port = -1;
        int depth = 0;

    };

    bool parse_url(const std::string& raw, Url& result);
}