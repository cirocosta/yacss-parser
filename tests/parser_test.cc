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

  Rule rule1 = driver.stylesheet.rules.front();

  EXPECT_EQ(rule1.selectors.size(), 1);
  EXPECT_EQ(rule1.declarations.size(), 1);
  EXPECT_EQ(rule1.declarations["margin"], "auto");

  Selector h1 = rule1.selectors[0];

  EXPECT_EQ(h1.tag, "h1");
  EXPECT_TRUE(h1.classes.empty());
  EXPECT_TRUE(h1.id.empty());
}

TEST(CSS, SimpleRuleWithSelectorDiscrimination) {
  bool debug = false;
  CSSDriver driver (debug, debug);
  const char* source =
    "h1.class#id {"
      "margin: auto;"
    "}";

  driver.parse_source(source);

  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  Rule rule1 = driver.stylesheet.rules.front();

  EXPECT_EQ(rule1.selectors.size(), 1);
  EXPECT_EQ(rule1.declarations.size(), 1);
  EXPECT_EQ(rule1.declarations["margin"], "auto");

  Selector h1 = rule1.selectors[0];

  EXPECT_EQ(h1.tag, "h1");
  EXPECT_EQ(h1.id, "id");
  EXPECT_EQ(h1.classes.size(), 1);
  EXPECT_EQ(h1.classes[0], "class");
}

