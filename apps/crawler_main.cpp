#include <iostream>
#include <string>

#include "../common/cli.h"
#include "../common/log.h"

int main(int argc, char* argv[]) {
    try{
        auto result = atlas::parse_arguments(argc,argv);

        if(!result.success) {
            atlas::log_error(result.error_message);
            return 2;
        }

        atlas::log_info("Atlas Crawler Starting");

        return 0;
    }

    catch(const std::exception& ex) {
        atlas::log_error(
            std::string("Unexpected application failure: ") + ex.what()
        );
        return 1;
    }
    catch(...) {
        atlas::log_error("Unexpected application failure: ");
        return 1;
    }
}