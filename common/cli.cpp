#include "cli.h"

#include <iostream>
#include <string>

namespace atlas {

ParseResult parse_arguements(int argc, char* argv[]) {
    Config config;
    bool has_max_pages = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help") {
            std::cout
                << "Usage: atlas-crawler [options]\n"
                << "\n"
                << "Options:\n"
                << "  --seed <URL>              Seed URL; repeatable\n"
                << "  --max-pages <N>           Maximum number of pages to crawl\n"
                << "  --timeout <seconds>       Per-request timeout\n"
                << "  --delay-ms <milliseconds> Minimum delay between requests\n"
                << "  --help                    Show usage information\n";

            return {true, {}, ""};
        }

        if (arg == "--seed") {
            if (i + 1 >= argc) {
                return {false, {}, "--seed requires a URL."};
            }

            config.seed_urls.push_back(argv[++i]);
        }
        else if (arg == "--max-pages") {
            if (i + 1 >= argc) {
                return {false, {}, "--max-pages requires a value."};
            }

            try {
                config.max_pages = std::stoi(argv[++i]);
            } catch (...) {
                return {false, {}, "--max-pages must be an integer."};
            }

            if (config.max_pages <= 0) {
                return {false, {}, "--max-pages must be greater than 0."};
            }

            has_max_pages = true;
        }
        else if (arg == "--timeout") {
            if (i + 1 >= argc) {
                return {false, {}, "--timeout requires a value."};
            }

            try {
                config.request_timeout_seconds = std::stoi(argv[++i]);
            } catch (...) {
                return {false, {}, "--timeout must be an integer."};
            }

            if (config.request_timeout_seconds <= 0) {
                return {false, {}, "--timeout must be greater than 0."};
            }
        }
        else if (arg == "--delay-ms") {
            if (i + 1 >= argc) {
                return {false, {}, "--delay-ms requires a value."};
            }

            try {
                config.crawl_delay_ms = std::stoi(argv[++i]);
            } catch (...) {
                return {false, {}, "--delay-ms must be an integer."};
            }

            if (config.crawl_delay_ms < 0) {
                return {false, {}, "--delay-ms cannot be negative."};
            }
        }
        else {
            return {false, {}, "unknown option: " + arg};
        }
    }

    if (config.seed_urls.empty()) {
        return {false, {}, "at least one --seed URL is required."};
    }

    if (!has_max_pages) {
        return {false, {}, "--max-pages is required."};
    }

    return {true, config, ""};
    }
}