#pragma once

#include<string>
#include<vector>

namespace atlas{
    struct Config{
        std::vector<std::string> seed_urls;

        int max_pages = 100;
        int request_timeout_seconds = 10;
        int crawl_delay_ms = 100;
    };
}