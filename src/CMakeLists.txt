BISON_TARGET(MyParser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc COMPILE_FLAGS "-y")
FLEX_TARGET(MyScanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(yacssparser
  ${FLEX_MyScanner_OUTPUTS}
  ${BISON_MyParser_OUTPUTS}
  driver.cc
  CSS.cc
)

