#ifndef YACSS__CSS_HH
#define YACSS__CSS_HH

#include "CSSBaseValue.hh"
#include "CSSValues.hh"

#include <vector>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <iostream>


namespace yacss {

class CSSDriver;
struct Stylesheet;
struct Rule;
struct Selector;

typedef std::pair<std::string, CSSBaseValue> Declaration;
typedef std::map<std::string, CSSBaseValue> DeclarationContainer;

typedef std::shared_ptr<Rule> RulePtr;
typedef std::vector<RulePtr> RulePtrContainer;

typedef std::vector<Selector> SelectorContainer;


struct Selector
{
  std::string tag;
  std::string id;
  std::vector<std::string> classes;
  bool universal = false;
  unsigned specificity = 0;

  inline bool operator< (const Selector& sel) const
  {
    return specificity < sel.specificity;
  }

  inline bool operator> (const Selector& sel) const
  {
    return specificity > sel.specificity;
  }
};

struct Stylesheet
{
  RulePtrContainer rules;
};

struct Rule
{
  SelectorContainer selectors;
  DeclarationContainer declarations;

  inline explicit Rule (SelectorContainer sel, DeclarationContainer decl)
    : selectors(sel), declarations(decl)
  {}
};


std::ostream& operator<<(std::ostream&, const Stylesheet&);

std::ostream& operator<<(std::ostream&, const Rule&);
std::ostream& operator<<(std::ostream&, const RulePtrContainer&);
std::ostream& operator<<(std::ostream&, const RulePtr&);

std::ostream& operator<<(std::ostream&, const Declaration&);
std::ostream& operator<<(std::ostream&, const DeclarationContainer&);

std::ostream& operator<<(std::ostream&, const Selector&);
std::ostream& operator<<(std::ostream&, const SelectorContainer&);

}; // !ns yacss

#endif

