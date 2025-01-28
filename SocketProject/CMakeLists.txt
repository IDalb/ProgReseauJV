cmake_minimum_required(VERSION 3.20)
project(SocketProject VERSION 1.0 LANGUAGES CXX)

# Collect source and header files
file(GLOB_RECURSE SOCKET_SOURCES src/*.cpp)
file(GLOB_RECURSE SOCKET_HEADERS include/*.h)

add_library(SocketProject STATIC ${SOCKET_SOURCES} ${SOCKET_HEADERS})
target_include_directories(SocketProject PUBLIC include)
