#ifndef YAHTML__DRIVER_HH
#define YAHTML__DRIVER_HH

#include <string>
#include <map>
#include "parser.hh"
#include "yacss/CSS.hh"

#define YY_DECL \
  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};

YY_DECL;

typedef struct yy_buffer_state * YY_BUFFER_STATE;

class CSSDriver
{
public:
  CSS stylesheet;
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

  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};


#endif
