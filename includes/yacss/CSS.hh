#ifndef YAHTML__CSS_HH
#define YAHTML__CSS_HH

#include <vector>
#include <map>
#include <string>
#include <utility>


class CSSDriver;

struct Stylesheet;
struct Rule;

typedef std::pair<std::string, std::string> Declaration;
typedef std::map<std::string, std::string> Declarations;

typedef std::vector<Rule> Ruleset;
typedef std::vector<std::string> Selectors;


struct Stylesheet
{
  Ruleset rules;
};

struct Rule
{
  std::vector<std::string> selectors;
  Declarations declarations;
};

#endif

