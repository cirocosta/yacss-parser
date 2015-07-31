#include "yacss/CSSValues.hh"
#include <sstream>

namespace yacss {

std::ostream& operator<< (std::ostream& o, const KeywordValue& k)
{
  o << k.val;
  return o;
}

std::ostream& operator<< (std::ostream& o, const LengthValue& l)
{
  o << l.val << l.unit;
  return o;
}

std::ostream& operator<< (std::ostream& o, const ColorRGBAValue& c)
{
  o << "rgba(" << (int)c.r << ","
               << (int)c.g << ","
               << (int)c.b << ","
               << (int)c.a
    << ")";

  return o;
}

}; // ! ns yacss

