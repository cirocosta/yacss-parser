#include <iostream>
#include <sstream>
#include "gtest/gtest.h"
#include "yacss/CSS.hh"

TEST(CSS, SimpleRule) {
  const char* expected =
    "h1 {\n"
      "margin: auto;\n"
    "}\n";
  std::ostringstream actual;

  Declaration decl {"margin", "auto"};
  Selectors selectors { "h1" };
  Rule rule { selectors, Declarations {decl} };
  Stylesheet ss { Rules {rule} };

  actual << ss;

  EXPECT_EQ(expected, actual.str());

}

