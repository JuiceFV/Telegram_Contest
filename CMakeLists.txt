# CMake min version, you can change it for the your own version
cmake_minimum_required(VERSION 3.15)

# The project name
project(Telegram_Contest)

# detect operating system
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")

# set project version
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}")

message("${PROJECT_NAME} version: ${${PROJECT_NAME}_VERSION}")



# Set sources variables
set(${PROJECT_NAME}_main "main.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_main})
