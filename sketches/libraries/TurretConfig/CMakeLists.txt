cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(TurretConfig ${headers_} ${sources_})

target_include_directories(TurretConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TurretConfig LINK_PUBLIC Arduino)