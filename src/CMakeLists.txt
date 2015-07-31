BISON_TARGET(MyParser yacss_parser.yy ${CMAKE_CURRENT_BINARY_DIR}/yacss_parser.cc)
FLEX_TARGET(MyScanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

set(INCLUDES "${INCLUDES}" "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
include_directories(${INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_library(yacssparser
  ${FLEX_MyScanner_OUTPUTS}
  ${BISON_MyParser_OUTPUTS}
  driver.cc
  CSSBaseValue.cc
  CSSValues.cc
  CSS.cc
)

set(BISON_HEADERS_PREFIX yacss)

configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/fix_bison_headers.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/fix_bison_headers.cmake
  @ONLY
)

add_custom_command(
  TARGET yacssparser PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/fix_bison_headers.cmake
)


set(LIBS "yacssparser" PARENT_SCOPE)

