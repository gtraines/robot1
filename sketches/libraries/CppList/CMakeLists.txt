cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME CppList)
project(${PROJECT_NAME})

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(CppList ${headers_} ${sources_})

add_library(${CMAKE_PROJECT_NAME} ${headers_} ${sources_})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})