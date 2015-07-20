cmake_minimum_required(VERSION 2.8)

# Turn it OFF: -Dtest=OFF
option(test "Include Tests." ON)

set(PROJECT_NAME yacss-parser)

project(${PROJECT_NAME} C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
    message(STATUS "Please use a different C++ compiler.")
endif()

find_package(BISON)
find_package(FLEX)


include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/includes
)

add_subdirectory(src/)

if (test)
  add_subdirectory(lib/googletest)
  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_subdirectory(tests/)
endif(test)

