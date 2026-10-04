#include "url.h"
#include <boost/url.hpp>

namespace atlas {
    bool parse_url(const std::string& raw, Url& result) {
        auto parsed = boost::urls::parse_uri(raw);

        if(!parsed) {
            return false;
        }

        auto url = parsed.value();

        result.raw = raw;
        result.normalized = raw;

        result.scheme = std::string(url.scheme());
        result.host = std::string(url.host());
        result.path = std::string(url.path());

        if(url.has_port()) {
            result.port = std::stoi(std::string(url.port()));
        }

        return true;
    }
}