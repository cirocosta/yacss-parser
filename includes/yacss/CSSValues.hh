#ifndef YACSS__CSSVALUES_HH
#define YACSS__CSSVALUES_HH

#include <string>
#include <array>
#include <sstream>
#include <cstring>

namespace yacss
{

enum class ValueType : unsigned char {
  Undefined,
  Keyword,
  Length,
  ColorRGBA,
};

enum UNIT { UNIT_PX, UNIT_CM, UNIT_PERCENT };

struct KeywordValue {
  std::string val;
  const ValueType type = ValueType::Keyword;

  inline explicit KeywordValue(std::string v) : val(v) {}

  inline static std::string parse(const char* text, size_t size)
  {
    unsigned i = 0;
    unsigned j = size;

    while (!::isgraph(text[++i]))
      ;
    while (!::isgraph(text[j - 1]) || text[j - 1] == ';')
      j--;

    return std::string(text + i, j - i);
  }

  inline bool operator==(const KeywordValue& other) const
  {
    return val == other.val;
  }
};

struct LengthValue {
  float val;
  UNIT unit;
  const ValueType type = ValueType::Length;

  inline explicit LengthValue(float v, UNIT u = UNIT_PX) : val(v), unit(u) {}

  inline static float parse(const char* text, size_t size)
  {
    return std::stof(text);
  }

  inline bool operator==(const LengthValue& other) const
  {
    return other.unit == unit && other.val == val;
  }
};

typedef std::array<unsigned char, 4> RGBA;

struct ColorRGBAValue {
  RGBA rgba;
  const ValueType type = ValueType::ColorRGBA;

  inline explicit ColorRGBAValue(RGBA rgba_) : rgba(rgba_) {}

  inline static RGBA parse(const char* text, size_t size)
  {
    RGBA rgba;
    unsigned i = 0;

    while (text[i++] != '#')
      ;

    rgba[0] = std::stoul(std::string(text, i, i + 2), NULL, 16);
    rgba[1] = std::stoul(std::string(text, i + 2, i + 4), NULL, 16);
    rgba[2] = std::stoul(std::string(text, i + 4, i + 6), NULL, 16);
    rgba[3] = 255;

    return rgba;
  }

  inline bool operator==(const ColorRGBAValue& other) const
  {
    return rgba == other.rgba;
  }
};

std::ostream& operator<<(std::ostream& o, const KeywordValue& k);
std::ostream& operator<<(std::ostream& o, const ColorRGBAValue& c);
std::ostream& operator<<(std::ostream& o, const LengthValue& l);

}; // ! ns yacss

#endif
