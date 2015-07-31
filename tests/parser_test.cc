#include "gtest/gtest.h"
#include "yacss/parser/driver.hh"

using namespace yacss;

TEST(CSS, SimpleRule) {
  bool debug = false;
  CSSDriver driver (debug, debug);
  const char* source =
    "h1 {"
      "margin-right: auto;"
      "margin-left: 200px;"
      "color: #ffffff;"
    "}";

  driver.parse_source(source);

  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();

  EXPECT_EQ(rule1->selectors.size(), 1);
  EXPECT_EQ(rule1->declarations.size(), 3);

  EXPECT_EQ(rule1->declarations["margin-right"].type, ValueType::Keyword);
  EXPECT_EQ(rule1->declarations["margin-right"].get<KeywordValue>().val, "auto");

  EXPECT_EQ(rule1->declarations["margin-left"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-left"].get<LengthValue>().val, 200);

  EXPECT_EQ(rule1->declarations["color"].type, ValueType::ColorRGBA);
  RGBA expected_color {255, 255, 255 ,255};
  EXPECT_EQ(rule1->declarations["color"].get<ColorRGBAValue>().rgba, expected_color);

  Selector h1 = rule1->selectors[0];

  EXPECT_EQ(h1.tag, "h1");
  EXPECT_TRUE(h1.classes.empty());
  EXPECT_TRUE(h1.id.empty());
}

/* TEST(CSS, SimpleRuleWithSelectorDiscrimination) { */
/*   bool debug = false; */
/*   CSSDriver driver (debug, debug); */
/*   const char* source = */
/*     "h1.class#id {" */
/*       "margin: auto;" */
/*     "}"; */

/*   driver.parse_source(source); */

/*   EXPECT_EQ(driver.stylesheet.rules.size(), 1); */

/*   RulePtr rule1 = driver.stylesheet.rules.front(); */

/*   EXPECT_EQ(rule1->selectors.size(), 1); */
/*   EXPECT_EQ(rule1->declarations.size(), 1); */
/*   EXPECT_EQ(rule1->declarations["margin"], "auto"); */

/*   Selector h1 = rule1->selectors[0]; */

/*   EXPECT_EQ(h1.tag, "h1"); */
/*   EXPECT_EQ(h1.id, "id"); */
/*   EXPECT_EQ(h1.classes.size(), 1); */
/*   EXPECT_EQ(h1.classes[0], "class"); */
/* } */

/* TEST(CSS, MultipleSelectorsAndMultipleClasses) { */
/*   bool debug = false; */
/*   CSSDriver driver (debug, debug); */
/*   const char* source = */
/*     "h1.class1.class2#id1," */
/*     "h2.class1.class2#id2," */
/*     "h3.class1.class2#id3 {" */
/*       "margin: auto;" */
/*       "width: 50%;" */
/*       "height: 300px;" */
/*     "}"; */

/*   driver.parse_source(source); */

/*   EXPECT_EQ(driver.stylesheet.rules.size(), 1); */

/*   RulePtr rule1 = driver.stylesheet.rules[0]; */

/*   EXPECT_EQ(rule1->selectors.size(), 3); */
/*   EXPECT_EQ(rule1->declarations.size(), 3); */
/*   EXPECT_EQ(rule1->declarations["margin"], "auto"); */
/*   EXPECT_EQ(rule1->declarations["width"], "50%"); */
/*   EXPECT_EQ(rule1->declarations["height"], "300px"); */

/*   Selector h1 = rule1->selectors[0]; */
/*   EXPECT_EQ(h1.tag, "h1"); */
/*   EXPECT_EQ(h1.id, "id1"); */
/*   EXPECT_EQ(h1.classes.size(), 2); */
/*   EXPECT_EQ(h1.classes[0], "class1"); */
/*   EXPECT_EQ(h1.classes[1], "class2"); */

/*   Selector h2 = rule1->selectors[1]; */
/*   EXPECT_EQ(h2.tag, "h2"); */
/*   EXPECT_EQ(h2.id, "id2"); */
/*   EXPECT_EQ(h2.classes.size(), 2); */
/*   EXPECT_EQ(h2.classes[0], "class1"); */
/*   EXPECT_EQ(h2.classes[1], "class2"); */

/*   Selector h3 = rule1->selectors[2]; */
/*   EXPECT_EQ(h3.tag, "h3"); */
/*   EXPECT_EQ(h3.id, "id3"); */
/*   EXPECT_EQ(h3.classes.size(), 2); */
/*   EXPECT_EQ(h3.classes[0], "class1"); */
/*   EXPECT_EQ(h3.classes[1], "class2"); */
/* } */

/* TEST(CSS, MultiSelectorWhiteSpaces) { */
/*   bool debug = false; */
/*   CSSDriver driver (debug, debug); */
/*   const char* source = */
/*     "/1* this is some cool css stuff *1/\n" */
/*     "h1.class1.class2#id1   ,\n" */
/*     "h2.class1.class2#id2\t\t,\n" */
/*     "h3.class1.class2#id3\n" */
/*     "{\n" */
/*       "\tmargin: auto;" */
/*       "\twidth: 50%;" */
/*       "\theight: 300px;\n" */
/*     "}"; */

/*   driver.parse_source(source); */

/*   EXPECT_EQ(driver.stylesheet.rules.size(), 1); */

/*   RulePtr rule1 = driver.stylesheet.rules[0]; */

/*   EXPECT_EQ(rule1->selectors.size(), 3); */
/*   EXPECT_EQ(rule1->declarations.size(), 3); */
/*   EXPECT_EQ(rule1->declarations["margin"], "auto"); */
/*   EXPECT_EQ(rule1->declarations["width"], "50%"); */
/*   EXPECT_EQ(rule1->declarations["height"], "300px"); */

/*   Selector h1 = rule1->selectors[0]; */
/*   EXPECT_EQ(h1.tag, "h1"); */
/*   EXPECT_EQ(h1.id, "id1"); */
/*   EXPECT_EQ(h1.classes.size(), 2); */
/*   EXPECT_EQ(h1.classes[0], "class1"); */
/*   EXPECT_EQ(h1.classes[1], "class2"); */

/*   Selector h2 = rule1->selectors[1]; */
/*   EXPECT_EQ(h2.tag, "h2"); */
/*   EXPECT_EQ(h2.id, "id2"); */
/*   EXPECT_EQ(h2.classes.size(), 2); */
/*   EXPECT_EQ(h2.classes[0], "class1"); */
/*   EXPECT_EQ(h2.classes[1], "class2"); */

/*   Selector h3 = rule1->selectors[2]; */
/*   EXPECT_EQ(h3.tag, "h3"); */
/*   EXPECT_EQ(h3.id, "id3"); */
/*   EXPECT_EQ(h3.classes.size(), 2); */
/*   EXPECT_EQ(h3.classes[0], "class1"); */
/*   EXPECT_EQ(h3.classes[1], "class2"); */
/* } */

/* TEST(CSS, Specificity) { */
/*   bool debug = false; */
/*   CSSDriver driver (debug, debug); */
/*   const char* source = */
/*     "h1.class#id {" */
/*       "margin: auto;" */
/*     "}"; */

/*   driver.parse_source(source); */

/*   EXPECT_EQ(driver.stylesheet.rules.size(), 1); */

/*   RulePtr rule1 = driver.stylesheet.rules.front(); */

/*   EXPECT_EQ(rule1->selectors.size(), 1); */
/*   EXPECT_EQ(rule1->declarations.size(), 1); */

/*   Selector h1 = rule1->selectors[0]; */

/*   EXPECT_EQ(h1.tag.empty(), false); */
/*   EXPECT_EQ(h1.id.empty(), false); */
/*   EXPECT_EQ(h1.classes.size(), 1); */

/*   EXPECT_EQ(h1.specificity, 111); */
/* } */

/* TEST(CSS, MultipleSelectorsSpecificity) { */
/*   bool debug = false; */
/*   CSSDriver driver (debug, debug); */
/*   const char* source = */
/*     "/1* this is some cool css stuff *1/\n" */
/*     "h2.class1.class2#id2\t\t,\n" */
/*     "h1.class1.class2.class3#id1   ,\n" */
/*     "h11\n" */
/*     "{\n" */
/*       "\tmargin: auto;" */
/*     "}"; */

/*   driver.parse_source(source); */

/*   EXPECT_EQ(driver.stylesheet.rules.size(), 1); */

/*   RulePtr rule1 = driver.stylesheet.rules[0]; */

/*   EXPECT_EQ(rule1->selectors.size(), 3); */
/*   EXPECT_EQ(rule1->declarations.size(), 1); */

/*   Selector h1 = rule1->selectors[0]; */
/*   EXPECT_EQ(h1.tag, "h1"); */
/*   EXPECT_EQ(h1.id, "id1"); */
/*   EXPECT_EQ(h1.classes.size(), 3); */
/*   EXPECT_EQ(h1.classes[0], "class1"); */
/*   EXPECT_EQ(h1.classes[1], "class2"); */
/*   EXPECT_EQ(h1.classes[2], "class3"); */
/*   EXPECT_EQ(h1.specificity, 131); */

/*   Selector h2 = rule1->selectors[1]; */
/*   EXPECT_EQ(h2.tag, "h2"); */
/*   EXPECT_EQ(h2.id, "id2"); */
/*   EXPECT_EQ(h2.classes.size(), 2); */
/*   EXPECT_EQ(h2.classes[0], "class1"); */
/*   EXPECT_EQ(h2.classes[1], "class2"); */
/*   EXPECT_EQ(h2.specificity, 121); */

/*   Selector h11 = rule1->selectors[2]; */
/*   EXPECT_EQ(h11.tag, "h11"); */
/*   EXPECT_EQ(h11.id.empty(), true); */
/*   EXPECT_EQ(h11.classes.size(), 0); */
/*   EXPECT_EQ(h11.specificity, 1); */
/* } */

