cmake_minimum_required(VERSION 3.20)
project(ClientProject VERSION 1.0 LANGUAGES CXX)

# Collect source and header files
file(GLOB_RECURSE CLIENT_SOURCES src/*.cpp)
file(GLOB_RECURSE CLIENT_HEADERS include/*.h)

# Create the executable
add_executable(ClientProject ${CLIENT_SOURCES} ${CLIENT_HEADERS})

# Include directories
target_include_directories(ClientProject PUBLIC include)

# Link with BeaverEngine
target_link_libraries(ClientProject PUBLIC SocketProject)