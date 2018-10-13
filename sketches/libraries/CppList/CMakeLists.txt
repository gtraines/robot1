cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(CppList ${headers_} ${sources_})
target_include_directories(CppList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})