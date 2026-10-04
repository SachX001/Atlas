#include "cli.h"

#include <iostream>
#include <string>

namespace atlas {

bool parse_arguements(int argc, char* argv[], Config& config) {
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

            return true;
        }

        if (arg == "--seed") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --seed requires a URL.\n";
                return false;
            }

            config.seed_urls.push_back(argv[++i]);
        }
        else if (arg == "--max-pages") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --max-pages requires a value.\n";
                return false;
            }

            try {
                config.max_pages = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Error: --max-pages must be an integer.\n";
                return false;
            }

            if (config.max_pages <= 0) {
                std::cerr << "Error: --max-pages must be greater than 0.\n";
                return false;
            }

            has_max_pages = true;
        }
        else if (arg == "--timeout") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --timeout requires a value.\n";
                return false;
            }

            try {
                config.request_timeout_seconds = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Error: --timeout must be an integer.\n";
                return false;
            }

            if (config.request_timeout_seconds <= 0) {
                std::cerr << "Error: --timeout must be greater than 0.\n";
                return false;
            }
        }
        else if (arg == "--delay-ms") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --delay-ms requires a value.\n";
                return false;
            }

            try {
                config.crawl_delay_ms = std::stoi(argv[++i]);
            } catch (...) {
                std::cerr << "Error: --delay-ms must be an integer.\n";
                return false;
            }

            if (config.crawl_delay_ms < 0) {
                std::cerr << "Error: --delay-ms cannot be negative.\n";
                return false;
            }
        }
        else {
            std::cerr << "Error: unknown option: " << arg << '\n';
            return false;
        }
    }

    if (config.seed_urls.empty()) {
        std::cerr << "Error: at least one --seed URL is required.\n";
        return false;
    }

    if (!has_max_pages) {
        std::cerr << "Error: --max-pages is required.\n";
        return false;
    }

    return true;
}

}