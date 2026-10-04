#include <gtest/gtest.h>

#include "../common/url.h"

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