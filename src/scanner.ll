%{ /* -*- C++ -*- */

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

#include "yacss/parser/driver.hh"
#include "parser.hh"

#undef yywrap
#define yywrap() 1

// The location of the current token.
static yy::location loc;

%}

%option noyywrap nounput batch debug noinput

%x DECL

OWS                 [\t ]*
COMMA               ","
LCB                 "{"
RCB                 "}"

NMSTART             [_a-zA-Z]
NMCHAR              [_a-zA-Z0-9-]

IDENT               -?{NMSTART}{NMCHAR}*
DECL_KEY            {IDENT}":"
DECL_VAL            " "[^:]";"

ELEM                {IDENT}|"*"
ID                  "#"{IDENT}
CLASS               "."{IDENT}


%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{ELEM}          return yy::CSSParser::make_ELEM(yytext, loc);
{ID}            return yy::CSSParser::make_ID(yytext, loc);
{CLASS}         return yy::CSSParser::make_CLASS(yytext, loc);
{COMMA}         return yy::CSSParser::make_COMMA(loc);

{LCB}           {
                  BEGIN(DECL);
                  return yy::CSSParser::make_LCB(loc);
                }

<DECL>{RCB}     {
                  BEGIN(INITIAL);
                  return yy::CSSParser::make_RCB(loc);
                }

<DECL>{DECL_KEY} {
                    return yy::CSSParser::make_DECL_KEY(
                        std::string(yytext, 0, yyleng-1), loc);
                  }

<DECL>{DECL_VAL} {
                    return yy::CSSParser::make_DECL_VAL(
                        std::string(yytext, 1, yyleng-1), loc);
                  }

.               driver.error(loc, "Invalid Character");

<<EOF>>         return yy::CSSParser::make_END(loc);

%%

void CSSDriver::scan_begin_source (const std::string& source)
{
  src = new char[source.size() + 1];
  std::copy(source.begin(), source.end(), src);
  src[source.size()] = '\0';

  yy_flex_debug = trace_scanning;
  buffer = yy_scan_string(src);
}


void CSSDriver::scan_end_source ()
{
  yy_delete_buffer(buffer);
  delete[] src;
}

void CSSDriver::scan_begin ()
{
  yy_flex_debug = trace_scanning;

  if (!(yyin = fopen(file.c_str(), "r"))) {
    error("Can't open " + file + ": " + strerror(errno));
    exit(EXIT_FAILURE);
  }

  buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
  yy_switch_to_buffer(buffer);
}

void CSSDriver::scan_destroy ()
{
  yylex_destroy();
}

void CSSDriver::scan_end ()
{
  yy_flush_buffer(buffer);
  yy_delete_buffer(buffer);
  fclose(yyin);
}

