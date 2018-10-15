file(GLOB headers_ "*.h")
file(GLOB sources_ "*.cpp")

add_library(IrTxRx ${headers_} ${sources_})

target_include_directories(IrTxRx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(IrTxRx LINK_PUBLIC Arduino)