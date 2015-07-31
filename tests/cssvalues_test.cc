#include "gtest/gtest.h"
#include "yacss/CSSValues.hh"

#include <cstring>

using namespace yacss;

TEST(Length, Pixels) {
  const char* text =
    " 20px;";
  size_t text_size = strlen(text);

  int expected = 20;
  int actual = LengthValue::parse(text, text_size);

  EXPECT_EQ(expected, actual);
}

TEST(Color, Hexadecimal) {
  const char* text =
    " #ffffff;";
  size_t text_size = strlen(text);

  RGBA expected = {255, 255, 255, 255};
  RGBA actual = ColorRGBAValue::parse(text, text_size);

  EXPECT_EQ(expected[0], actual[0]);
  EXPECT_EQ(expected[1], actual[1]);
  EXPECT_EQ(expected[2], actual[2]);
  EXPECT_EQ(expected[3], actual[3]);
}

TEST(Keyword, Alphabetic) {
  const char* text =
    " auto;";
  size_t text_size = strlen(text);

  std::string expected = "auto";
  std::string actual = KeywordValue::parse(text, text_size);

  EXPECT_EQ(expected, actual);
}

TEST(Keyword, SpacedWithQuotes) {
  const char* text =
    " 'Helvetica Neue';";
  size_t text_size = strlen(text);

  std::string expected = "'Helvetica Neue'";
  std::string actual = KeywordValue::parse(text, text_size);

  EXPECT_EQ(expected, actual);
}

