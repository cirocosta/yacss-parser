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
  o << "rgba(" << (int)c.rgba[0] << ","
               << (int)c.rgba[1] << ","
               << (int)c.rgba[2] << ","
               << (int)c.rgba[3]
    << ")";

  return o;
}

}; // ! ns yacss

