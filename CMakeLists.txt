cmake_minimum_required(VERSION 3.20)
project(TheSocket VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(ClientProject)
add_subdirectory(ServerProject)
add_subdirectory(SocketProject)