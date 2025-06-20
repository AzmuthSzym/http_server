cmake_minimum_required(VERSION 3.20)
project(HTTPServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()
include(FetchContent)

# Add executable
add_executable(http_server 
    src/main.cpp 
    src/server.cpp
    src/http_utils.cpp
)

# Create test executable
add_executable(tests
  tests/test_main.cpp
  tests/test_http_utils.cpp
)

# Link Google Test to your test executable
target_link_libraries(tests
  gtest_main
  gtest
)

# Link Winsock library on Windows
if(WIN32)
    target_link_libraries(http_server ws2_32 wsock32)
endif()

# Include directories for tests
target_include_directories(tests PRIVATE src)

# Add tests to CMake's test runner
include(GoogleTest)
gtest_discover_tests(tests)

# Fetch Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)