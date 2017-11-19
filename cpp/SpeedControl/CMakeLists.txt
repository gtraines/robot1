cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME SpeedControl)
project(${PROJECT_NAME})

include_directories("${PROJECT_BINARY_DIR}")

set(${CMAKE_PROJECT_NAME}_SKETCH test_harness.ino)
#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
set(uno.build.mcu atmega2560)
set(uno.upload.protocol wiring)
set(uno.upload.speed 115200)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
