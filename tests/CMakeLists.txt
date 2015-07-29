include_directories(${yacss-parser_INCLUDES})

add_executable(parser_test parser_test.cc)
add_executable(css_test css_test.cc)

target_link_libraries(parser_test gtest gtest_main ${yacss-parser_LIBS})
target_link_libraries(css_test gtest gtest_main ${yacss-parser_LIBS})

add_test(NAME parser_test COMMAND parser_test)
add_test(NAME css_test COMMAND css_test)

add_custom_command(
  TARGET parser_test PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:parser_test>/assets
)

