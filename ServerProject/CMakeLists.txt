cmake_minimum_required(VERSION 3.20)
project(ServerProject VERSION 1.0 LANGUAGES CXX)

# Collect source and header files
file(GLOB_RECURSE SERVER_SOURCES src/*.cpp)
file(GLOB_RECURSE SERVER_HEADERS include/*.h)

# Create the executable
add_executable(ServerProject ${SERVER_SOURCES} ${SERVER_HEADERS})

# Include directories
target_include_directories(ServerProject PUBLIC include)

# Link with BeaverEngine
target_link_libraries(ServerProject PUBLIC SocketProject)