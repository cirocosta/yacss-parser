#ifndef YACSS__CSS_HH
#define YACSS__CSS_HH

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
struct Value;

typedef std::shared_ptr<Value> ValuePtr;
typedef std::pair<std::string, ValuePtr> Declaration;
typedef std::map<std::string, ValuePtr> DeclarationContainer;

typedef std::shared_ptr<Rule> RulePtr;
typedef std::vector<RulePtr> RulePtrContainer;

typedef std::vector<Selector> SelectorContainer;


enum class ValueType
{
  Keyword, ColorRGBA, Length
};

struct Keyword;
struct ColorRGBA;
struct Length;

struct Value
{
  ValueType type;
  virtual ~Value()
  {}

  static std::shared_ptr<Keyword> getKeyword(const ValuePtr& val)
  {
    return std::static_pointer_cast<Keyword>(val);
  }
};

struct Keyword : public Value
{
  inline explicit Keyword (std::string val) :
    value(val)
  {
    type = ValueType::Keyword;
  }

  std::string value;
};

struct ColorRGBA : public Value
{
  inline explicit ColorRGBA (unsigned char cr, unsigned char cg, unsigned char cb)
    : r(cr), g(cg), b(cb)
  {
    type = ValueType::ColorRGBA;
  }

  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a = 255;
};

struct Length : public Value
{
  inline explicit Length (std::string u, int val)
    : unit(u), value(val)
  {
    type = ValueType::Length;
  }

  std::string unit;
  int value;
};


struct Selector
{
  std::string tag;
  std::string id;
  std::vector<std::string> classes;
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

std::ostream& operator<<(std::ostream& o, const ValuePtr&);
std::ostream& operator<<(std::ostream& o, const Keyword&);
std::ostream& operator<<(std::ostream& o, const ColorRGBA&);
std::ostream& operator<<(std::ostream& o, const Length&);

}; // !ns yacss

#endif

