cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

include_directories(../Arduino_FreeRTOS)
include_directories(../CppList)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(PotMotorRtos ${headers_} ${sources_})
target_include_directories(PotMotorRtos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(PotMotorRtos LINK_PUBLIC CppList)
