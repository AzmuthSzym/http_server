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

# Add this near the end of your CMakeLists.txt
add_custom_command(TARGET http_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/public $<TARGET_FILE_DIR:http_server>/public
    COMMENT "Copying public folder to build directory"
)

# Link Winsock library on Windows
if(WIN32)
    target_link_libraries(http_server ws2_32)
endif()

# Include directories (if you have a separate include folder)
target_include_directories(http_server PRIVATE include)