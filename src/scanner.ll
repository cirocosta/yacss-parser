%{ /* -*- C++ -*- */

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>

#include "yacss/parser/driver.hh"
#include "yacss_parser.hh"

#undef yywrap
#define yywrap() 1
#define YY_DECL yacss::CSSParser::symbol_type yylex (yacss::CSSDriver& driver)
YY_DECL;

// The location of the current token.
static yacss::location loc;

%}

%option noyywrap nounput batch debug noinput
%option prefix="yacss"

%x DECL

OWS                 [ \r\n\f\t]*
COMMA               {OWS}","{OWS}
SC                  {OWS}";"{OWS}
LCB                 "{"{OWS}
RCB                 {OWS}"}"{OWS}

HEX                 [0-9a-fA-F]
DIGIT               [0-9]
NMSTART             [_a-zA-Z]
NMCHAR              [_a-zA-Z0-9-]
FLOAT               ({DIGIT}*".")?{DIGIT}+

IDENT               -?{NMSTART}{NMCHAR}*

DECL_KEY            {IDENT}":"

DECL_STR            " "+[^:\r\n;}{]+
DECL_PX             " "+{FLOAT}"px"?
DECL_HEXC           " "+"#"{HEX}{6}

STAR                "*"
ELEM                {IDENT}
ID                  "#"{IDENT}
CLASS               "."{IDENT}

COMMENTS            {OWS}\/\*[^*]*\*+([^/*][^*]*\*+)*\/{OWS}


%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{COMMENTS}  {}
<DECL>{COMMENTS}  {}

{ELEM}          return yacss::CSSParser::make_ELEM(yytext, loc);

{STAR}          return yacss::CSSParser::make_STAR(loc);

{ID}            return yacss::CSSParser::make_ID(yytext+1, loc);

{CLASS}         return yacss::CSSParser::make_CLASS(yytext+1, loc);


{COMMA}         return yacss::CSSParser::make_COMMA(loc);

{OWS}           return yacss::CSSParser::make_OWS(loc);

{LCB}           {
                  BEGIN(DECL);
                  return yacss::CSSParser::make_LCB(loc);
                }


<DECL>{RCB}     {
                  BEGIN(INITIAL);
                  return yacss::CSSParser::make_RCB(loc);
                }

<DECL>{SC}        { return yacss::CSSParser::make_SC(loc); }

<DECL>{DECL_KEY}  {
                    return yacss::CSSParser::make_DECL_KEY(
                      std::string(yytext, 0, yyleng-1), loc);
                  }

<DECL>{DECL_PX}   {
                    float val = yacss::LengthValue::parse(yytext, yyleng);

                    return yacss::CSSParser::make_DECL_VAL(
                      yacss::LengthValue(val, yacss::UNIT_PX), loc);
                  }

<DECL>{DECL_HEXC} {
                    yacss::RGBA rgba =
                      yacss::ColorRGBAValue::parse(yytext, yyleng);

                    return yacss::CSSParser::make_DECL_VAL(
                      yacss::ColorRGBAValue(rgba), loc);
                  }

<DECL>{DECL_STR} {
                    std::string str =
                      yacss::KeywordValue::parse(yytext, yyleng);

                    return yacss::CSSParser::make_DECL_VAL(
                      yacss::KeywordValue(str), loc);
                 }

.               driver.error(loc, "Invalid Character");

<<EOF>>         return yacss::CSSParser::make_END(loc);

%%

void yacss::CSSDriver::scan_begin_source (const std::string& source)
{
  src = new char[source.size() + 1];
  std::copy(source.begin(), source.end(), src);
  src[source.size()] = '\0';

  yy_flex_debug = trace_scanning;
  buffer = yy_scan_string(src);
}


void yacss::CSSDriver::scan_end_source ()
{
  yy_delete_buffer(buffer);
  delete[] src;
}

void yacss::CSSDriver::scan_begin ()
{
  yy_flex_debug = trace_scanning;

  if (!(yyin = fopen(file.c_str(), "r"))) {
    error("Can't open " + file + ": " + strerror(errno));
    exit(EXIT_FAILURE);
  }

  buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
  yy_switch_to_buffer(buffer);
}

void yacss::CSSDriver::scan_destroy ()
{
  yylex_destroy();
}

void yacss::CSSDriver::scan_end ()
{
  yy_flush_buffer(buffer);
  yy_delete_buffer(buffer);
  fclose(yyin);
}

#undef YY_DECL

