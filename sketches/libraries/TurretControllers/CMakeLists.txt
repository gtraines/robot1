cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME TurretControllers)
project(${PROJECT_NAME})

include_directories(../Arduino_FreeRTOS)
include_directories(../TurretConfig)
include_directories(../PotMotor)
include_directories(../Indicator)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(${CMAKE_PROJECT_NAME} ${headers_} ${sources_})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})