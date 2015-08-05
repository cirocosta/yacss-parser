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
  o << l.val;

  switch (l.unit) {
    case UNIT_PX:
      o << "px";
      break;
    case UNIT_CM:
      o << "cm";
      break;
    case UNIT_PERCENT:
      o << "%";
      break;
    default:
      throw std::runtime_error("unrecognized unit");
  }


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

