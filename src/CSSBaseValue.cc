#include "yacss/CSSBaseValue.hh"

namespace yacss {

std::ostream& operator<< (std::ostream& o, const CSSBaseValue& val)
{
  if (val.type == ValueType::Length)
    o << val.get<LengthValue>();
  else if (val.type == ValueType::Keyword)
    o << val.get<KeywordValue>();
  else if (val.type == ValueType::ColorRGBA)
    o << val.get<ColorRGBAValue>();
  else
    throw std::runtime_error("CSSBaseValue << : Unknown Type.");
  return o;
}

}; // ! ns yacss

