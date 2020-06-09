cmake_minimum_required(VERSION 3.9)

project(Telegram_Context)

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}")

message("${PROJECT_NAME} version: ${${PROJECT_NAME}_VERSION}")

include(cmake/safeguard.cmake)
include(cmake/setflags.cmake)

set(SL_SOURCES "./solution/sources/")
set(PS_SOURCES "./solution/parser/")
set(TST_SOURCES "./solution/tests")
set(${PROJECT_NAME}_MAIN "main.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_MAIN})