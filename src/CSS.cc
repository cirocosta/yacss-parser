#include "yacss/CSS.hh"


std::ostream& operator<<(std::ostream& o, const Stylesheet& ss)
{
  o << ss.rules;

  return o;
}

std::ostream& operator<<(std::ostream& o, const Rule& rule)
{
  o << rule.selectors << "{" << std::endl
    << rule.declarations << std::endl
    << "}";

  return o;
}

std::ostream& operator<<(std::ostream& o, const Rules& rules)
{
  for (const auto& rule : rules)
    o << rule << std::endl;

  return o;
}

std::ostream& operator<<(std::ostream& o, const Declaration& declaration)
{
  o << declaration.first << ": " << declaration.second << ";";

  return o;
}

std::ostream& operator<<(std::ostream& o, const Declarations& declarations)
{
  for (const auto& declaration : declarations)
    o << declaration;

  return o;
}

std::ostream& operator<<(std::ostream& o, const Selector& selector)
{
  if (!selector.tag.empty())
    o << selector.tag;

  if (!selector.id.empty())
    o << "#" << selector.id;

  if (!selector.classes.empty()) {
    for (const auto& klass : selector.classes)
      o << "." << klass;
  }

  return o;
}

std::ostream& operator<<(std::ostream& o, const Selectors& selectors)
{
  for (const auto& selector : selectors)
    o << selector << " ";

  return o;
}


