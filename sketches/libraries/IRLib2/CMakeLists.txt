file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(IRLib2 ${headers_} ${sources_})

target_include_directories(IRLib2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IRLib2 LINK_PUBLIC Arduino)