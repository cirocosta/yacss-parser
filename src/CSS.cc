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
    << rule.declarations
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
  for (const Declaration& declaration : declarations)
    o << "\t" << declaration << std::endl;

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

}; // !ns yacss

