cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME Arduino_FreeRTOS)
project(${PROJECT_NAME})

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.c")

add_library(${CMAKE_PROJECT_NAME} ${headers_} ${sources_})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})