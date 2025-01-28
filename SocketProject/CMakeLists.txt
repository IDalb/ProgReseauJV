cmake_minimum_required(VERSION 3.20)
project(SocketProject VERSION 1.0 LANGUAGES CXX)

# Collect source and header files
file(GLOB_RECURSE SOCKET_SOURCES src/*.cpp)
file(GLOB_RECURSE SOCKET_HEADERS include/*.h)

add_library(SocketProject STATIC ${SOCKET_SOURCES} ${SOCKET_HEADERS})
target_include_directories(SocketProject PUBLIC include)

#include dependencies
#target_include_directories(BeaverEngine PUBLIC ${lib_name_SOURCE_DIR}/include)
# Link external libraries
#target_link_libraries(SocketProject
#    PUBLIC
#        lib_name
#)

set_target_properties(SocketProject PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
