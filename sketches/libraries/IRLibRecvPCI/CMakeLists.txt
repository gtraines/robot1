file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(IRLibRecvPCI ${headers_} ${sources_})

target_include_directories(IRLibRecvPCI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IRLibRecvPCI LINK_PUBLIC Arduino)
target_link_libraries(IRLibRecvPCI LINK_PUBLIC IRLib2)