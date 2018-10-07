cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/ArduinoToolchain.cmake)
set(PROJECT_NAME turretFreeRtos)
project(${PROJECT_NAME})

include_directories(../libraries/Arduino_FreeRTOS)
include_directories(../libraries/TurretConfig)
include_directories(../libraries/Indicator)
include_directories(../libraries/CppList)
include_directories(../libraries/PotMotor)
include_directories(../libraries/TurretControllers)

set(${CMAKE_PROJECT_NAME}_SKETCH turretFreeRtos.ino)

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD mega)
set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})