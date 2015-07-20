#ifndef YAHTML__CSS_HH
#define YAHTML__CSS_HH

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>


class CSSDriver;

struct Stylesheet;
struct Rule;

struct Declaration : std::pair<std::string, std::string>
{
  using std::pair<std::string, std::string>::pair;
};

struct Declarations : std::map<std::string, std::string>
{
  using std::map<std::string, std::string>::map;
};

typedef std::vector<Rule> Rules;
typedef std::vector<std::string> Selectors;


struct Stylesheet
{
  Rules rules;
};

struct Rule
{
  Selectors selectors;
  Declarations declarations;
};


std::ostream& operator<<(std::ostream& o, const Stylesheet&);
std::ostream& operator<<(std::ostream& o, const Rule&);
std::ostream& operator<<(std::ostream& o, const Rules&);
std::ostream& operator<<(std::ostream& o, const Declaration&);
std::ostream& operator<<(std::ostream& o, const Declarations&);
std::ostream& operator<<(std::ostream& o, const Selectors&);

#endif

