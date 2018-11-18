cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

include_directories(../Arduino_FreeRTOS)
include_directories(../TurretConfig)
include_directories(../PotMotor)
include_directories(../Indicator)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(TurretControllers ${headers_} ${sources_})

target_include_directories(TurretControllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TurretControllers LINK_PUBLIC IRremote)
target_link_libraries(TurretControllers LINK_PUBLIC IRLibProtocols)
target_link_libraries(TurretControllers LINK_PUBLIC Arduino_FreeRTOS)
target_link_libraries(TurretControllers LINK_PUBLIC TurretConfig)
target_link_libraries(TurretControllers LINK_PUBLIC PotMotor)
target_link_libraries(TurretControllers LINK_PUBLIC Indicator)