#ifndef YACSS__DRIVER_HH
#define YACSS__DRIVER_HH

#include <string>
#include <map>
#include "parser.hh"
#include "yacss/CSS.hh"

/* #define YY_DECL yacss::CSSParser::symbol_type yylex (yacss::CSSDriver& driver) */
/* YY_DECL; */

namespace yacss {

typedef struct yy_buffer_state * YY_BUFFER_STATE;

class CSSDriver
{
public:
  Stylesheet  stylesheet;
  int result;

  std::string file;
  YY_BUFFER_STATE buffer;
  char* src;

  bool trace_scanning;
  bool trace_parsing;

public:
  CSSDriver();
  CSSDriver(bool ts, bool tp);
  virtual ~CSSDriver();

public:
  void parse(const std::string& file);
  void parse_source(const std::string& file);

  void scan_begin();
  void scan_begin_source(const std::string& source);
  void scan_end();
  void scan_end_source();
  void scan_destroy();

  void error(const location& l, const std::string& m);
  void error(const std::string& m);
};

}; // !ns yacss

#endif
