#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "../common/url.h"
#include "../common/document.h"
#include "../common/crawl_state.h"
#include "../common/config.h"
#include "../common/cli.h"
#include "../common/log.h"

TEST(AtlasUrlTest, ParsesBasicUrl) {
    atlas::Url url;

    ASSERT_TRUE(atlas::parse_url(
        "https://example.com:8080/products/laptop",
        url
    ));

    EXPECT_EQ(url.scheme, "https");
    EXPECT_EQ(url.host, "example.com");
    EXPECT_EQ(url.port, 8080);
    EXPECT_EQ(url.path, "/products/laptop");
}

TEST(DocumentTest, StoresDocumentData) {
    atlas::Document document;

    document.url.raw = "https://example.com";
    document.title = "Example";
    document.text = "This is an example page.";

    atlas::Url link;
    link.raw = "https://example.com/about";
    document.links.push_back(link);

    EXPECT_EQ(document.url.raw, "https://example.com");
    EXPECT_EQ(document.title, "Example");
    EXPECT_EQ(document.text, "This is an example page.");
    ASSERT_EQ(document.links.size(), 1);
    EXPECT_EQ(document.links[0].raw, "https://example.com/about");
}

TEST(CrawlStateTest, HasExpectedStates) {
    atlas::CrawlState state = atlas::CrawlState::Discovered;

    EXPECT_EQ(state, atlas::CrawlState::Discovered);

    state = atlas::CrawlState::Queued;
    EXPECT_EQ(state, atlas::CrawlState::Queued);

    state = atlas::CrawlState::Fetching;
    EXPECT_EQ(state, atlas::CrawlState::Fetching);

    state = atlas::CrawlState::Fetched;
    EXPECT_EQ(state, atlas::CrawlState::Fetched);

    state = atlas::CrawlState::Failed;
    EXPECT_EQ(state, atlas::CrawlState::Failed);
}

TEST(ConfigTest, StoresConfiguration) {
    atlas::Config config;

    config.seed_urls = {"https://example.com", "https://example.org"};
    config.max_pages = 500;
    config.request_timeout_seconds = 20;
    config.crawl_delay_ms = 250;

    ASSERT_EQ(config.seed_urls.size(), 2);
    EXPECT_EQ(config.seed_urls[0], "https://example.com");
    EXPECT_EQ(config.seed_urls[1], "https://example.org");

    EXPECT_EQ(config.max_pages, 500);
    EXPECT_EQ(config.request_timeout_seconds, 20);
    EXPECT_EQ(config.crawl_delay_ms, 250);
}

TEST(CliTest, ParsesValidArguments) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--seed", "https://example.org",
        "--max-pages", "500",
        "--timeout", "20",
        "--delay-ms", "250"
    };

    auto result = atlas::parse_arguments(
    static_cast<int>(std::size(argv)),
    const_cast<char**>(argv)
    );

    ASSERT_TRUE(result.success);

    const auto& config = result.config;

    ASSERT_EQ(config.seed_urls.size(), 2);
    EXPECT_EQ(config.seed_urls[0], "https://example.com");
    EXPECT_EQ(config.seed_urls[1], "https://example.org");

    EXPECT_EQ(config.max_pages, 500);
    EXPECT_EQ(config.request_timeout_seconds, 20);
    EXPECT_EQ(config.crawl_delay_ms, 250);
}

TEST(CliTest, RejectsMissingSeed) {
    const char* argv[] = {
        "atlas-crawler",
        "--max-pages", "100"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
   EXPECT_EQ(
        result.error_message,
        "at least one --seed URL is required."
    );
}

TEST(CliTest, RejectsMissingMaxPages) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(result.error_message.find("--max-pages"), std::string::npos);
}

TEST(CliTest, RejectsInvalidMaxPages) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--max-pages", "0"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(result.error_message.find("greater than 0"), std::string::npos);
}

TEST(CliTest, RejectsInvalidTimeout) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--max-pages", "100",
        "--timeout", "0"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(
        result.error_message.find("--timeout"),
        std::string::npos
    );
}

TEST(CliTest, RejectsNegativeDelay) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--max-pages", "100",
        "--delay-ms", "-1"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(
        result.error_message.find("--delay-ms"),
        std::string::npos
    );
}

TEST(CliTest, RejectsMissingSeedValue) {
    const char* argv[] = {
        "atlas-crawler",
        "--max-pages", "100",
        "--seed"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(
        result.error_message.find("--seed"),
        std::string::npos
    );
}

TEST(CliTest, RejectsMissingMaxPagesValue) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--max-pages"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(
        result.error_message.find("--max-pages"),
        std::string::npos
    );
}

TEST(CliTest, RejectsMissingTimeoutValue) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--max-pages", "100",
        "--timeout"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(
        result.error_message.find("--timeout"),
        std::string::npos
    );
}

TEST(CliTest, RejectsMissingDelayValue) {
    const char* argv[] = {
        "atlas-crawler",
        "--seed", "https://example.com",
        "--max-pages", "100",
        "--delay-ms"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(
        result.error_message.find("--delay-ms"),
        std::string::npos
    );
}

TEST(CliTest, AcceptsHelp) {
    const char* argv[] = {
        "atlas-crawler",
        "--help"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_TRUE(result.success);
}

TEST(CliTest, RejectsUnknownOption) {
    const char* argv[] = {
        "atlas-crawler",
        "--something"
    };

    auto result = atlas::parse_arguments(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv)
    );

    EXPECT_FALSE(result.success);
    EXPECT_NE(result.error_message.find("unknown option"), std::string::npos);
}

TEST(LogTest, CanLogMessage) {
    atlas::log_info("info message");
    atlas::log_warn("warning message");
    atlas::log_error("error message");
}
