#include "gtest/gtest.h"
#include "yacss/CSS.hh"

#include <iostream>
#include <memory>
#include <functional>
#include <algorithm>
#include <sstream>

using namespace yacss;

TEST(CSSPrinting, SimpleRule) {
  std::ostringstream actual;
  const char* expected =
    "h1 {\n"
      "margin: auto;\n"
    "}\n";

  auto val = std::make_shared<Keyword>("auto");

  Declaration decl {"margin", val};
  Selector h1;
  h1.tag = "h1";

  SelectorContainer selectors { h1 };
  RulePtr rule = std::make_shared<Rule>(selectors, DeclarationContainer {decl});
  Stylesheet ss { RulePtrContainer{rule} };

  actual << ss;

  EXPECT_EQ(expected, actual.str());
}

TEST(CSSPrinting, RuleWithMultipleValues) {
  std::ostringstream actual;
  const char* expected =
    "h1 {\n"
      "margin: auto;\n"
      "width: 200px;\n"
      "color: rgba(10,20,30,255);\n"
    "}\n";

  auto margin_val = std::make_shared<Keyword>("auto");
  auto width_val = std::make_shared<Length>(200);
  auto color_val = std::make_shared<ColorRGBA>(10,20,30);

  Declaration margin {"margin", margin_val };
  Declaration width {"width", width_val };
  Declaration color {"color", color_val };

  Selector h1;
  h1.tag = "h1";

  SelectorContainer selectors { h1 };
  RulePtr rule = std::make_shared<Rule>(selectors,
                                        DeclarationContainer {margin,width,color});
  Stylesheet ss { RulePtrContainer{rule} };

  actual << ss;

  EXPECT_EQ(expected, actual.str());
}

TEST(SelectorContainer, Sorting) {
  Selector sel1;
  sel1.specificity = 100;

  Selector sel2;
  sel2.specificity = 200;

  Selector sel3;
  sel3.specificity = 300;

  SelectorContainer selectors {sel1, sel3, sel2};
  std::sort(selectors.begin(), selectors.end(), std::greater<Selector>());

  EXPECT_EQ(sel3.specificity, selectors[0].specificity);
  EXPECT_EQ(sel2.specificity, selectors[1].specificity);
  EXPECT_EQ(sel1.specificity, selectors[2].specificity);
}

