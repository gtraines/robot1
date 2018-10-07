cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME PotMotor)
project(${PROJECT_NAME})

include_directories(../Arduino_FreeRTOS)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_subdirectory(../CppList)

add_library(${CMAKE_PROJECT_NAME} ${headers_} ${sources_})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} LINK_PUBLIC CppList)
