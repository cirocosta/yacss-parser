#include "gtest/gtest.h"
#include "yacss/parser/driver.hh"

TEST(CSS, SimpleRule) {
  bool debug = false;
  CSSDriver driver (debug, debug);
  const char* source =
    "h1 {"
      "margin: auto;"
    "}";

  driver.parse_source(source);

  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  Rule h1 = driver.stylesheet.rules.front();

  EXPECT_EQ(h1.selectors[0], "h1");
  EXPECT_EQ(h1.declarations.size(), 1);
  EXPECT_EQ(h1.declarations["margin"], "auto");
}

