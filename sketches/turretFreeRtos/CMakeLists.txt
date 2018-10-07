cmake_minimum_required(VERSION 3.10)

include_directories(../libraries/Arduino_FreeRTOS/)
include_directories(../libraries/TurretConfig/)
include_directories(../libraries/Indicator/)
include_directories(../libraries/CppList/)
include_directories(../libraries/PotMotor/)
include_directories(../libraries/TurretControllers/)

file(GLOB turret_config_ ../libraries/TurretConfig/*.h)
file(GLOB turret_controllers_ ../libraries/TurretControllers/*.h)

add_executable(turretFreeRtos turretFreeRtos.ino ${turret_config_} ${turret_controllers_})

target_link_libraries(turretFreeRtos LINK_PUBLIC Arduino_FreeRTOS)
target_link_libraries(turretFreeRtos LINK_PUBLIC TurretConfig)
target_link_libraries(turretFreeRtos LINK_PUBLIC Indicator)
target_link_libraries(turretFreeRtos LINK_PUBLIC CppList)
target_link_libraries(turretFreeRtos LINK_PUBLIC PotMotor)
target_link_libraries(turretFreeRtos LINK_PUBLIC TurretControllers)

