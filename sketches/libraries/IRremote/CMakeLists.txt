file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(IRremote ${headers_} ${sources_})

target_include_directories(IRremote PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IRremote LINK_PUBLIC Arduino)