cmake_minimum_required(VERSION 3.20)
project(TheSocket VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define dependency paths
set(DEPS_DIR ${CMAKE_SOURCE_DIR}/_deps)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Add external libraries
include(FetchContent)

# Lib
#FetchContent_Declare(
#    lib_name
#    GIT_REPOSITORY https://github.com/...
#    GIT_TAG master
#)
#FetchContent_MakeAvailable(glfw)

# Add subdirectories
add_subdirectory(ClientProject)

# Add subdirectories
add_subdirectory(ServerProject)

# Add subdirectories
add_subdirectory(SocketProject)