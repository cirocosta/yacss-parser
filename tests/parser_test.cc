#include "gtest/gtest.h"
#include "yacss/parser/driver.hh"

using namespace yacss;

TEST(CSS, SimpleRule)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1 {"
                       "margin-right: auto;"
                       "margin-left: 200px;"
                       "color: #ffffff;"
                       "}";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();
  ASSERT_EQ(rule1->declarations.size(), 3);

  EXPECT_EQ(rule1->declarations["margin-right"].type, ValueType::Keyword);
  EXPECT_EQ(rule1->declarations["margin-right"].get<KeywordValue>().val,
            "auto");

  EXPECT_EQ(rule1->declarations["margin-left"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-left"].get<LengthValue>().val, 200);

  EXPECT_EQ(rule1->declarations["color"].type, ValueType::ColorRGBA);
  RGBA expected_color{ 255, 255, 255, 255 };
  EXPECT_EQ(rule1->declarations["color"].get<ColorRGBAValue>().rgba,
            expected_color);

  ASSERT_EQ(rule1->selectors.size(), 1);
  Selector h1 = rule1->selectors[0];

  EXPECT_EQ(h1.tag, "h1");
  EXPECT_TRUE(h1.classes.empty());
  EXPECT_TRUE(h1.id.empty());
}

TEST(CSS, SimpleRuleWithFloats)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1 {"
                       "margin-top: 0;"
                       "margin-bottom: .5px;"
                       "margin-left: 10.5px;"
                       "margin-right: 10px"
                       "}";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();
  EXPECT_EQ(rule1->selectors.size(), 1);
  ASSERT_EQ(rule1->declarations.size(), 4);

  ASSERT_EQ(rule1->declarations["margin-top"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-top"].get<LengthValue>().val, 0);

  ASSERT_EQ(rule1->declarations["margin-right"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-right"].get<LengthValue>().val, 10);

  ASSERT_EQ(rule1->declarations["margin-bottom"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-bottom"].get<LengthValue>().val, 0.5);

  ASSERT_EQ(rule1->declarations["margin-left"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-left"].get<LengthValue>().val, 10.5);
}

TEST(CSS, SimpleRuleWithSelectorDiscrimination)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1.class#id {"
                       "margin: auto;"
                       "}";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();

  ASSERT_EQ(rule1->selectors.size(), 1);
  ASSERT_EQ(rule1->declarations.size(), 1);
  ASSERT_EQ(rule1->declarations["margin"].type, ValueType::Keyword);

  Selector h1 = rule1->selectors[0];

  EXPECT_EQ(h1.tag, "h1");
  EXPECT_EQ(h1.id, "id");
  EXPECT_EQ(h1.classes.size(), 1);
  EXPECT_EQ(h1.classes[0], "class");
}

TEST(CSS, MultipleSelectorsAndMultipleClasses)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1.class1.class2#id1,"
                       "h2.class1.class2#id2,"
                       "h3.class1.class2#id3 {"
                       "margin: auto;"
                       "width: 200px;"
                       "height: 300px;"
                       "}";

  driver.parse_source(source);

  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules[0];

  EXPECT_EQ(rule1->selectors.size(), 3);
  EXPECT_EQ(rule1->declarations.size(), 3);
  EXPECT_EQ(rule1->declarations["margin"].get<KeywordValue>().val, "auto");
  EXPECT_EQ(rule1->declarations["width"].get<LengthValue>().val, 200);
  EXPECT_EQ(rule1->declarations["height"].get<LengthValue>().val, 300);

  Selector h1 = rule1->selectors[0];
  EXPECT_EQ(h1.tag, "h1");
  EXPECT_EQ(h1.id, "id1");
  EXPECT_EQ(h1.classes.size(), 2);
  EXPECT_EQ(h1.classes[0], "class1");
  EXPECT_EQ(h1.classes[1], "class2");

  Selector h2 = rule1->selectors[1];
  EXPECT_EQ(h2.tag, "h2");
  EXPECT_EQ(h2.id, "id2");
  EXPECT_EQ(h2.classes.size(), 2);
  EXPECT_EQ(h2.classes[0], "class1");
  EXPECT_EQ(h2.classes[1], "class2");

  Selector h3 = rule1->selectors[2];
  EXPECT_EQ(h3.tag, "h3");
  EXPECT_EQ(h3.id, "id3");
  EXPECT_EQ(h3.classes.size(), 2);
  EXPECT_EQ(h3.classes[0], "class1");
  EXPECT_EQ(h3.classes[1], "class2");
}

TEST(CSS, MultiSelectorWhiteSpaces)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "/* this is some cool css stuff */\n"
                       "h1.class1.class2#id1   ,\n"
                       "h2.class1.class2#id2\t\t,\n"
                       "h3.class1.class2#id3\n"
                       "{\n"
                       "\tmargin: auto;"
                       "\twidth: 200px;"
                       "\theight: 300px;\n"
                       "}";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules[0];

  EXPECT_EQ(rule1->selectors.size(), 3);
  EXPECT_EQ(rule1->declarations.size(), 3);
  EXPECT_EQ(rule1->declarations["margin"].get<KeywordValue>().val, "auto");
  EXPECT_EQ(rule1->declarations["width"].get<LengthValue>().val, 200);
  EXPECT_EQ(rule1->declarations["height"].get<LengthValue>().val, 300);

  Selector h1 = rule1->selectors[0];
  EXPECT_EQ(h1.tag, "h1");
  EXPECT_EQ(h1.id, "id1");
  EXPECT_EQ(h1.classes.size(), 2);
  EXPECT_EQ(h1.classes[0], "class1");
  EXPECT_EQ(h1.classes[1], "class2");

  Selector h2 = rule1->selectors[1];
  EXPECT_EQ(h2.tag, "h2");
  EXPECT_EQ(h2.id, "id2");
  EXPECT_EQ(h2.classes.size(), 2);
  EXPECT_EQ(h2.classes[0], "class1");
  EXPECT_EQ(h2.classes[1], "class2");

  Selector h3 = rule1->selectors[2];
  EXPECT_EQ(h3.tag, "h3");
  EXPECT_EQ(h3.id, "id3");
  EXPECT_EQ(h3.classes.size(), 2);
  EXPECT_EQ(h3.classes[0], "class1");
  EXPECT_EQ(h3.classes[1], "class2");
}

TEST(CSS, Specificity)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1.class#id {"
                       "margin: auto;"
                       "}";

  driver.parse_source(source);

  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();

  EXPECT_EQ(rule1->selectors.size(), 1);
  EXPECT_EQ(rule1->declarations.size(), 1);

  Selector h1 = rule1->selectors[0];

  EXPECT_EQ(h1.tag.empty(), false);
  EXPECT_EQ(h1.id.empty(), false);
  EXPECT_EQ(h1.classes.size(), 1);

  EXPECT_EQ(h1.specificity, 111);
}

TEST(CSS, MultipleSelectorsSpecificity)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "/* this is some cool css stuff */\n"
                       "h2.class1.class2#id2\t\t,\n"
                       "h1.class1.class2.class3#id1   ,\n"
                       "h11\n"
                       "{\n"
                       "\tmargin: auto;"
                       "}";

  driver.parse_source(source);

  EXPECT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules[0];

  EXPECT_EQ(rule1->selectors.size(), 3);
  EXPECT_EQ(rule1->declarations.size(), 1);

  Selector h1 = rule1->selectors[0];
  EXPECT_EQ(h1.tag, "h1");
  EXPECT_EQ(h1.id, "id1");
  EXPECT_EQ(h1.classes.size(), 3);
  EXPECT_EQ(h1.classes[0], "class1");
  EXPECT_EQ(h1.classes[1], "class2");
  EXPECT_EQ(h1.classes[2], "class3");
  EXPECT_EQ(h1.specificity, 131);

  Selector h2 = rule1->selectors[1];
  EXPECT_EQ(h2.tag, "h2");
  EXPECT_EQ(h2.id, "id2");
  EXPECT_EQ(h2.classes.size(), 2);
  EXPECT_EQ(h2.classes[0], "class1");
  EXPECT_EQ(h2.classes[1], "class2");
  EXPECT_EQ(h2.specificity, 121);

  Selector h11 = rule1->selectors[2];
  EXPECT_EQ(h11.tag, "h11");
  EXPECT_EQ(h11.id.empty(), true);
  EXPECT_EQ(h11.classes.size(), 0);
  EXPECT_EQ(h11.specificity, 1);
}

TEST(CSS, UniversalSelectorOnly)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "/* no confusion with comments*/"
                       "* {"
                       "margin: auto;"
                       "}";

  driver.parse_source(source);

  ASSERT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();
  ASSERT_EQ(rule1->selectors.size(), 1);
  ASSERT_EQ(rule1->declarations.size(), 1);

  Selector universal = rule1->selectors[0];
  ASSERT_EQ(universal.tag.empty(), false);
  ASSERT_EQ(universal.tag, "*");
  ASSERT_EQ(universal.id.empty(), true);
  ASSERT_EQ(universal.classes.empty(), true);

  EXPECT_EQ(universal.specificity, 0);
}

TEST(CSS, LastPropWithoutSemicolon)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1 {"
                       "margin-right: auto;"
                       "margin-left: 200px"
                       "}";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.stylesheet.rules.size(), 1);

  RulePtr rule1 = driver.stylesheet.rules.front();
  ASSERT_EQ(rule1->selectors.size(), 1);
  ASSERT_EQ(rule1->declarations.size(), 2);
  EXPECT_EQ(rule1->declarations["margin-right"].type, ValueType::Keyword);
  EXPECT_EQ(rule1->declarations["margin-right"].get<KeywordValue>().val,
            "auto");
  EXPECT_EQ(rule1->declarations["margin-left"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-left"].get<LengthValue>().val, 200);

  Selector h1 = rule1->selectors[0];
  EXPECT_EQ(h1.tag, "h1");
  EXPECT_TRUE(h1.classes.empty());
  EXPECT_TRUE(h1.id.empty());
}

TEST(CSS, NoSemicolonInTheMiddle)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1 {"
                       "margin-left: 200px"
                       "margin-right: auto;"
                       "}";

  driver.parse_source(source);
  EXPECT_EQ(driver.result, 1);
}

TEST(CSS, CommentsBefore)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "\t/*\tmy cool\ncomment */"
                       "h1 {"
                       "margin-right: auto;"
                       "margin-left: 200px"
                       "}";

  driver.parse_source(source);
  EXPECT_EQ(driver.result, 0);
  RulePtr rule1 = driver.stylesheet.rules.front();
  EXPECT_EQ(rule1->declarations["margin-right"].type, ValueType::Keyword);
  EXPECT_EQ(rule1->declarations["margin-right"].get<KeywordValue>().val,
            "auto");
  EXPECT_EQ(rule1->declarations["margin-left"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-left"].get<LengthValue>().val, 200);
}

TEST(CSS, CommentsAnywhere)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "\t/*\tmy cool\ncomment */"
                       "h1 {"
                       "\t/*\tmy cool\ncomment */"
                       "margin-right: auto;"
                       "margin-left: 200px"
                       "}\n"
                       "\t/*\tmy cool\ncomment */";

  driver.parse_source(source);
  EXPECT_EQ(driver.result, 0);
  RulePtr rule1 = driver.stylesheet.rules.front();
  EXPECT_EQ(rule1->declarations["margin-right"].type, ValueType::Keyword);
  EXPECT_EQ(rule1->declarations["margin-right"].get<KeywordValue>().val,
            "auto");
  EXPECT_EQ(rule1->declarations["margin-left"].type, ValueType::Length);
  EXPECT_EQ(rule1->declarations["margin-left"].get<LengthValue>().val, 200);
}

TEST(CSS, MultipleRules)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "body, h1 { display: block; }"
                       "h1 { height: 10px }"
                       "body {"
                       "  display: block;"
                       "  width: 100px;"
                       "}";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  EXPECT_EQ(driver.stylesheet.rules.size(), 3);

  const CSSBaseValue& height =
      driver.stylesheet.rules.at(1)->declarations.at("height");
  EXPECT_EQ(height.get<LengthValue>().val, 10.0);
}

TEST(CSS, MultipleOnelinerRules)
{
  bool debug = false;
  CSSDriver driver(debug, debug);
  const char* source = "h1 { color: black }"
                       ".header1 {color: green }"
                       ".header2 {color: yellow }"
                       ".header,h1,h2,h3 {color: #abcdef }";

  driver.parse_source(source);
  ASSERT_EQ(driver.result, 0);
  EXPECT_EQ(driver.stylesheet.rules.size(), 4);
}
