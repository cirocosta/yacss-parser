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
  if (selector.universal)
    o << "*";

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
  SelectorContainer::const_iterator it;

  for (it = selectors.begin(); it != selectors.end()-1; it++)
    o << *it << ",\n";
  o << *it << " ";

  return o;
}

}; // !ns yacss

