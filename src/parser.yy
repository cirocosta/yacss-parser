%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"

%defines
%define parser_class_name {CSSParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include "yacss/CSS.hh"
}

// passing the parsing context
%param { CSSDriver& driver }

%locations
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
}

%define api.token.prefix {HTML_}
%token
  END 0             "End of File (EOF)"
  COMMA             ","
  LCB               "{"
  RCB               "}"
;

%token <std::string>
  ELEM
  ID
  CLASS

  DECL_KEY
  DECL_VAL
;

%type <Stylesheet> stylesheet;

%type <Rule> rule;
%type <Rules> rules;

%type <Declaration> declaration;
%type <Declarations> declarations;

%type <std::string> selector;
%type <Selectors> selectors;

/* %printer { yyoutput << $$; } <*>; */

%%

%start stylesheet;

stylesheet: rules {
                      driver.stylesheet = Stylesheet { $1 };
                      $$ = driver.stylesheet;
                    }
          ;

rule: selectors '{' declarations '}'  { $$ = Rule {$1, $3}; }
    ;

rules: %empty           { $$ = Rules {}; }
       | rule           { $$ = Rules { $1 }; }
       | rules rule     { $1.push_back($2); $$ = $1; }
       ;

selector: ELEM
        | ID
        | CLASS
        ;

selectors: selector               { $$ = Selectors{ $1 }; }
         | selectors ',' selector { $1.push_back($3); $$ = $1; }
         ;

declarations: %empty                    { $$ = Declarations {}; }
            | declaration               { $$ = Declarations { $1 }; }
            | declarations declaration  {
                                          $1.emplace($2);
                                          $$ = $1;
                                        }
            ;

declaration: DECL_KEY DECL_VAL { $$ = Declaration {$1, $2}; }
           ;

%%

void yy::CSSParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

