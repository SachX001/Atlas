#pragma once

#include <string>
#include<vector>
#include "url.h"

namespace atlas{

    struct Document {
        Url url;

        std::string title;
        std::string text;

        std::vector<Url> links;
    };
}