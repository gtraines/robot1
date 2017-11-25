cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME SpeedControl)
project(${PROJECT_NAME})

include_directories("/home/graham/arduino-1.8.5/hardware/arduino/avr/cores/arduino")
include_directories("/home/graham/arduino-1.8.5/hardware/arduino/avr/variants/standard")
include_directories("/home/graham/arduino-1.8.5/libraries/Servo/src")
include_directories("/home/graham/arduino-1.8.5/libraries/QueueList")
include_directories("${PROJECT_BINARY_DIR}")
set(SOURCE_FILES
        SpeedControlCommand.h
        InternalOperation.h
        SpeedControlOperation.h
        SpeedControlSpeed.h
        SpeedControl.h
        SpeedControl.cpp
        StackArray.h
        keywords.txt)
set(${CMAKE_PROJECT_NAME}_SKETCH test_harness.ino)
#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD uno)
#set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
#set(uno.build.mcu atmega2560)
#set(uno.upload.protocol wiring)
#set(uno.upload.speed 115200)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
