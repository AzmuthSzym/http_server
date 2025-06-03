cmake_minimum_required(VERSION 3.20)
project(HTTPServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(http_server 
    src/main.cpp 
    src/server.cpp
    src/http_utils.cpp
)

# Link Winsock library on Windows
if(WIN32)
    target_link_libraries(http_server ws2_32)
endif()

# Include directories (if you have a separate include folder)
target_include_directories(http_server PRIVATE include)