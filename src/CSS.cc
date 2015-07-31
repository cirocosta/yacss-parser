#include "yacss/CSS.hh"

namespace yacss {

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

std::ostream& operator<<(std::ostream& o, const RulePtr& rule)
{
  o << *rule;

  return o;
}

std::ostream& operator<<(std::ostream& o, const RulePtrContainer& rules)
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

std::ostream& operator<<(std::ostream& o, const DeclarationContainer& declarations)
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

std::ostream& operator<<(std::ostream& o, const SelectorContainer& selectors)
{
  for (const auto& selector : selectors)
    o << selector << " ";

  return o;
}

std::ostream& operator<<(std::ostream& o, const ValuePtr& v)
{
  if (v->type == ValueType::ColorRGBA) {
    o << *static_cast<ColorRGBA*>(v.get());
  } else if (v->type == ValueType::Keyword) {
    o << *static_cast<Keyword*>(v.get());
  } else if (v->type == ValueType::Length) {
    o << *static_cast<Length*>(v.get());
  } else {
    throw std::runtime_error("ValuePtr: unrecognized type.");
  }

  return o;
}

std::ostream& operator<<(std::ostream& o, const Keyword& k)
{
  o << k.value;
  return o;
}

std::ostream& operator<<(std::ostream& o, const ColorRGBA& c)
{
  o << "rgba(" << c.r << "," << c.g << "," << c.b << "," << c.a << ")";
  return o;
}

std::ostream& operator<<(std::ostream& o, const Length& l)
{
  o << l.value << l.unit;
  return o;
}

}; // !ns yacss

