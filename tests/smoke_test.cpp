#include <gtest/gtest.h>

#include "../common/url.h"
#include "../common/document.h"

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