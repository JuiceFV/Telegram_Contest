cmake_minimum_required(VERSION 3.14)
project(NgramLangDetection)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(NgramLangDetection src/main.cpp includes/main.h src/print_map.cpp)
