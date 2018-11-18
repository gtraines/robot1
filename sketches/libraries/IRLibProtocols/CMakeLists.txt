file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(IRLibProtocols ${headers_} ${sources_})

target_include_directories(IRLibProtocols PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IRLibProtocols LINK_PUBLIC Arduino)