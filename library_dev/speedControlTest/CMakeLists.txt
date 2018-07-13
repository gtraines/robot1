cmake_minimum_required(VERSION 3.8)
project(speedControlTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Servo.h
        Arduino.h
        Print.h
        SpeedControlSpeed.h
        SpeedControlOperation.h
        InternalOperation.cpp
        SpeedControlCommand.cpp
        SpeedControl.cpp
        main.cpp)
add_executable(speedControlTest ${SOURCE_FILES})