cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME Arduino_FreeRTOS)
project(${PROJECT_NAME})

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.c")

add_library(Arduino_FreeRTOS ${headers_} ${sources_})
target_include_directories(Arduino_FreeRTOS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})