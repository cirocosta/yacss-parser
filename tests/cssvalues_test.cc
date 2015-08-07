#include "gtest/gtest.h"
#include "yacss/CSSValues.hh"
#include "yacss/CSSBaseValue.hh"

#include <cstring>

using namespace yacss;

TEST(Length, IntegerPixelsWithSemicolon)
{
  const char* text = " 20px;";
  size_t text_size = strlen(text);

  int expected = 20;
  int actual = LengthValue::parse(text, text_size);

  EXPECT_EQ(expected, actual);
}

TEST(Length, IntegerPixelsWoutSemicolon)
{
  const char* text = " 20px\n";
  size_t text_size = strlen(text);

  EXPECT_EQ(LengthValue::parse(text, text_size), 20);
}

TEST(Length, FloatPixels)
{
  const char* text1 = "0.5px\n";
  const char* text2 = " .5px\n";

  EXPECT_EQ(LengthValue::parse(text1, strlen(text1)), 0.5);
  EXPECT_EQ(LengthValue::parse(text2, strlen(text2)), 0.5);
}

TEST(Color, Hexadecimal)
{
  const char* text = " #ffffff;";
  size_t text_size = strlen(text);

  RGBA expected = { 255, 255, 255, 255 };
  RGBA actual = ColorRGBAValue::parse(text, text_size);

  EXPECT_EQ(expected[0], actual[0]);
  EXPECT_EQ(expected[1], actual[1]);
  EXPECT_EQ(expected[2], actual[2]);
  EXPECT_EQ(expected[3], actual[3]);
}

TEST(Keyword, AlphabeticWithSemicolon)
{
  const char* text = " auto;";
  size_t text_size = strlen(text);

  EXPECT_EQ("auto", KeywordValue::parse(text, text_size));
}

TEST(Keyword, AlphabeticWithoutSemicolon)
{
  const char* text = " auto";
  size_t text_size = strlen(text);

  std::string expected = "auto";
  std::string actual = KeywordValue::parse(text, text_size);

  EXPECT_EQ(expected, actual);
}

TEST(Keyword, SpacedWithQuotes)
{
  const char* text = " 'Helvetica Neue';";
  size_t text_size = strlen(text);

  std::string expected = "'Helvetica Neue'";
  std::string actual = KeywordValue::parse(text, text_size);

  EXPECT_EQ(expected, actual);
}

TEST(CSSBaseValue, Equality)
{
  CSSBaseValue zero_length = LengthValue(0, UNIT_PX);
  LengthValue zero_length2 (0, UNIT_PX);
  CSSBaseValue zero_percent_length = LengthValue(0, UNIT_PERCENT);
  CSSBaseValue one_length = LengthValue(1, UNIT_PX);
  CSSBaseValue zero_kw_length = KeywordValue("0px");
  CSSBaseValue zero_kw = KeywordValue("0");
  KeywordValue zero_kw_length2 ("0px");

  EXPECT_FALSE(zero_length == one_length);
  EXPECT_FALSE(zero_length == zero_percent_length);
  EXPECT_TRUE(zero_length == zero_length2);
  EXPECT_TRUE(zero_length == zero_length);
  EXPECT_FALSE(zero_length == zero_kw_length);
  EXPECT_FALSE(zero_length == zero_kw_length);
  EXPECT_FALSE(zero_kw_length == zero_kw);
  EXPECT_TRUE(zero_kw_length == zero_kw_length2);
}
