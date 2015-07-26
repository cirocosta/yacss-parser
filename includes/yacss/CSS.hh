#ifndef YACSS__CSS_HH
#define YACSS__CSS_HH

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>

namespace yacss {

class CSSDriver;

struct Stylesheet;
struct Rule;
struct Selector;

struct Declaration : std::pair<std::string, std::string>
{
  using std::pair<std::string, std::string>::pair;
};

struct Declarations : std::map<std::string, std::string>
{
  using std::map<std::string, std::string>::map;
};

typedef std::vector<Rule> Rules;
typedef std::vector<Selector> Selectors;

struct Selector
{
  std::string tag;
  std::string id;
  std::vector<std::string> classes;
};

struct Stylesheet
{
  Rules rules;
};

struct Rule
{
  Selectors selectors;
  Declarations declarations;
};


std::ostream& operator<<(std::ostream&, const Stylesheet&);
std::ostream& operator<<(std::ostream&, const Rule&);
std::ostream& operator<<(std::ostream&, const Rules&);
std::ostream& operator<<(std::ostream&, const Declaration&);
std::ostream& operator<<(std::ostream&, const Declarations&);
std::ostream& operator<<(std::ostream&, const Selector&);
std::ostream& operator<<(std::ostream&, const Selectors&);

}; // !ns yacss

#endif

