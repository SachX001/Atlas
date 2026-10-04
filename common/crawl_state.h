#pragma once

namespace atlas{

    enum class CrawlState{
        Discovered,
        Queued,
        Fetching,
        Fetched,
        Failed,
    };
}