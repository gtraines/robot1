cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

include_directories(../Arduino_FreeRTOS)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(Taskr ${headers_} ${sources_})

target_include_directories(Taskr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Taskr LINK_PUBLIC Arduino_FreeRTOS)