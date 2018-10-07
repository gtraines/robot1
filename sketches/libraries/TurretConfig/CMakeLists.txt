cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME TurretControllers)
project(${PROJECT_NAME})

include_directories(${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES})

add_library(TurretConfig TurretPins.h TraverseConfig.h IrConfig.h IndicatorConfig.h ElevationConfig.h TurretConfigPlacard.cpp TurretConfigPlacard.h ../TurretControllers/TurretController.cpp)

target_include_directories(TurretConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TurretConfig LINK_PUBLIC Arduino)