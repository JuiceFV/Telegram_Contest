# CMake min version, you can change it for the your own version
cmake_minimum_required(VERSION 3.15)

# The project name
project(Telegram_Contest_1)

set(${PROJECT_NAME}_main "sources/main.cxx")
set(${PROJECT_NAME}_src "sources/html.cxx")
set(${PROJECT_NAME}_header "includes/html.hpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_main} ${${PROJECT_NAME}_src} ${${PROJECT_NAME}_header})
target_include_directories(${PROJECT_NAME} PRIVATE "includes")