#include <iostream>
#include <sstream>
#include "gtest/gtest.h"
#include "yacss/CSS.hh"

TEST(CSS, SimpleRule) {
  std::ostringstream actual;
  const char* expected =
    "h1 {\n"
      "margin: auto;\n"
    "}\n";

  Declaration decl {"margin", "auto"};
  Selector h1;
  h1.tag = "h1";

  Selectors selectors { h1 };
  Rule rule { selectors, Declarations {decl} };
  Stylesheet ss { Rules {rule} };

  actual << ss;

  EXPECT_EQ(expected, actual.str());
}

