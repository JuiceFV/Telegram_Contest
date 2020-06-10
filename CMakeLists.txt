# setting min demanded version
cmake_minimum_required(VERSION 3.9)

# setting project name
project(Telegram_Context)

# setting version of the project
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}")

# print the name and the version of the project
message("${PROJECT_NAME} version: ${${PROJECT_NAME}_VERSION}")

# including appropriate build for each OS
include(cmake/safeguard.cmake)

# including compile-flags for each OS
include(cmake/setflags.cmake)

# setting up variables for paths to solution, parser, tests
set(SOLUTION_SOURCE_DIR "./sources/solution")
set(PARSER_SOURCE_DIR "./sources/parser")
set(TESTS_SOURCE_DIR "./sources/tests")

set(${PROJECT_NAME}_PARSER_SOURCES 
"${PARSER_SOURCE_DIR}/document.cpp" 
"${PARSER_SOURCE_DIR}/document.h" 
"${PARSER_SOURCE_DIR}/tag_detector.cpp"
"${PARSER_SOURCE_DIR}/tag_detector.h"
"${PARSER_SOURCE_DIR}/util.cpp"
"${PARSER_SOURCE_DIR}/util.h")

# setting variables for sources file
set(${PROJECT_NAME}_MAIN "main.cpp")

add_library(parser STATIC ${${PROJECT_NAME}_PARSER_SOURCES})

# adding an executable with name <PROJECT_NAME>
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_MAIN})
target_link_libraries(${PROJECT_NAME} PRIVATE ${parser})