
file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

include_directories(../Arduino_FreeRTOS)
include_directories(../TurretConfig)
include_directories(../Indicator)
include_directories(../IrTxRx)

add_library(IrSensorCluster ${headers_} ${sources_})

target_include_directories(IrSensorCluster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IrSensorCluster LINK_PUBLIC Arduino)
target_link_libraries(IrSensorCluster LINK_PUBLIC IrTxRx)