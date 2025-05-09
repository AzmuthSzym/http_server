cmake_minimum_required(VERSION 3.20)
project(HTTPServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(http_server src/main.cpp src/server.cpp)

# Link Winsock library
target_link_libraries(http_server ws2_32)