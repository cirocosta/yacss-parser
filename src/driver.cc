#include "yacss/parser/driver.hh"
#include "parser.hh"

namespace yacss {

CSSDriver::CSSDriver ()
  : trace_scanning(false), trace_parsing(false)
{
}

CSSDriver::CSSDriver (bool ts, bool tp)
  : trace_scanning(ts), trace_parsing(tp)
{
}

CSSDriver::~CSSDriver()
{
  scan_destroy();
}

void CSSDriver::parse (const std::string &f)
{
  file = f;
  scan_begin();
  CSSParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
}

void CSSDriver::parse_source (const std::string &source)
{
  scan_begin_source(source);
  CSSParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end_source();
}

void CSSDriver::error (const yacss::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void CSSDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

}; // !ns yacss

