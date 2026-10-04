#include <gtest/gtest.h>

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

    atlas::Config config;

    ASSERT_TRUE(atlas::parse_arguements(
        static_cast<int>(std::size(argv)),
        const_cast<char**>(argv),
        config
    ));

    ASSERT_EQ(config.seed_urls.size(), 2);
    EXPECT_EQ(config.seed_urls[0], "https://example.com");
    EXPECT_EQ(config.seed_urls[1], "https://example.org");

    EXPECT_EQ(config.max_pages, 500);
    EXPECT_EQ(config.request_timeout_seconds, 20);
    EXPECT_EQ(config.crawl_delay_ms, 250);
}

TEST(LogTest, CanLogMessage) {
    atlas::log_info("info message");
    atlas::log_warn("warning message");
    atlas::log_error("error message");
}