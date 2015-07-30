%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"

%define api.prefix {yacss}
%define api.namespace {yacss}
%define parser_class_name {CSSParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include <functional>
#include <memory>
#include "yacss/CSS.hh"
}

// passing the parsing context
%param { CSSDriver& driver }

%initial-action
{
  // Initialize the initial location
  @$.begin.filename = @$.end.filename = &driver.file;
};

%define parse.trace
%define parse.error verbose

%code
{
#include "yacss/parser/driver.hh"
#define YY_DECL yacss::CSSParser::symbol_type yylex (yacss::CSSDriver& driver)
YY_DECL;
}

%define api.token.prefix {HTML_}
%token
  END 0             "End of File (EOF)"
  COMMA             ","
  LCB               "{"
  RCB               "}"
  OWS               " "
;

%token <std::string>
  ELEM
  ID
  CLASS

  DECL_KEY
  DECL_VAL
;

%type <Stylesheet> stylesheet;

%type <RulePtr> rule;
%type <RulePtrContainer> rules;

%type <Declaration> declaration;
%type <DeclarationContainer> declarations;

%type <Selector> selector;
%type <SelectorContainer> selectors;

%printer { yyoutput << $$; } <*>;

%%

%start stylesheet;

stylesheet
  : rules {
  driver.stylesheet = Stylesheet { $1 };
  $$ = driver.stylesheet;
          }
  ;


rules
  : %empty         { $$ = RulePtrContainer {}; }
  | rule           { $$ = RulePtrContainer { $1 }; }
  | rules rule     { $1.push_back($2); $$ = $1; }
  ;

rule
  : selectors OWS LCB declarations RCB {
  std::sort($1.begin(), $1.end(), std::greater<Selector>());
  $$ = std::make_shared<Rule>($1, $4);
                                       }
  ;


selectors
  : selector                 { $$ = SelectorContainer{ $1 }; }
  | selectors COMMA selector { $1.push_back($3); $$ = $1; }
  ;

selector
  : ELEM            {
  Selector sel;

  sel.tag = $1; sel.specificity += 1;
  $$ = sel;
                    }
  | ID              {
  Selector sel;

  sel.id = $1; sel.specificity += 100;
  $$ = sel;
                    }
  | CLASS           {
  Selector sel;

  sel.specificity += 10;
  sel.classes = std::vector<std::string> { $1 };
  $$ = sel;
                    }
  | selector ELEM   { $1.tag = $2; $1.specificity += 1; $$ = $1; }
  | selector ID     { $1.id = $2; $1.specificity += 100; $$ = $1; }
  | selector CLASS  {
  $1.classes.push_back($2);
  $1.specificity += 10;
  $$ = $1;
                    }
  ;


declarations
  : %empty                    { $$ = DeclarationContainer {}; }
  | declaration               { $$ = DeclarationContainer { $1 }; }
  | declarations declaration  { $1.emplace($2); $$ = $1; }
  ;

declaration
  : DECL_KEY DECL_VAL { $$ = Declaration {$1, $2}; }
  ;

%%

void yacss::CSSParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

#undef YY_DECL

