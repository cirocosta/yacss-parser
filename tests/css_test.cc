#include <iostream>
#include <functional>
#include <algorithm>
#include <sstream>
#include "gtest/gtest.h"
#include "yacss/CSS.hh"

using namespace yacss;

TEST(CSSPrinting, SimpleRule) {
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

TEST(Selectors, Sorting) {
  Selector sel1;
  sel1.specificity = 100;

  Selector sel2;
  sel2.specificity = 200;

  Selector sel3;
  sel3.specificity = 300;

  Selectors selectors {sel1, sel3, sel2};
  std::sort(selectors.begin(), selectors.end(), std::greater<Selector>());

  EXPECT_EQ(sel3.specificity, selectors[0].specificity);
  EXPECT_EQ(sel2.specificity, selectors[1].specificity);
  EXPECT_EQ(sel1.specificity, selectors[2].specificity);
}

