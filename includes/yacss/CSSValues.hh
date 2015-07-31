#ifndef YACSS__CSSVALUES_HH
#define YACSS__CSSVALUES_HH

#include <string>
#include <sstream>

namespace yacss {

enum class ValueType : unsigned char
{
  Undefined,
  Keyword, Length, ColorRGBA,
};


struct KeywordValue
{
  inline explicit KeywordValue (std::string v)
    : val(v)
  {}

  std::string val;
  const ValueType type = ValueType::Keyword;
};

struct LengthValue
{
  inline explicit LengthValue (int v, std::string u)
    : val(v), unit(u)
  {}

  int val;
  std::string unit;
  const ValueType type = ValueType::Length;
};

typedef unsigned char uchar;

struct ColorRGBAValue
{
  inline explicit ColorRGBAValue (uchar r_, uchar g_, uchar b_, uchar a_ = 255)
    : r(r_), g(g_), b(b_), a(a_)
  {}

  uchar r, g, b, a;
  const ValueType type = ValueType::ColorRGBA;
};

std::ostream& operator<< (std::ostream& o, const KeywordValue& k);
std::ostream& operator<< (std::ostream& o, const ColorRGBAValue& c);
std::ostream& operator<< (std::ostream& o, const LengthValue& l);

}; // ! ns yacss

#endif

