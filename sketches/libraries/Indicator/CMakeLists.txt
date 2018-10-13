cmake_minimum_required(VERSION 3.8)

include_directories(~/arduino-1.8.5/hardware/arduino/avr/cores/arduino)
include_directories(../Arduino_FreeRTOS)
include_directories(../TurretConfig)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(Indicator ${headers_} ${sources_})
target_include_directories(Indicator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
