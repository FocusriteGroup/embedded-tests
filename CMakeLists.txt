cmake_minimum_required(VERSION 3.20)
project(AudioFilterManager VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Fetch Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(Catch2)

# Add the FilterManager library
add_library(FilterManager
    src/FilterManager.cpp
)

target_include_directories(FilterManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add compiler warnings
if(MSVC)
    target_compile_options(FilterManager PRIVATE /W4)
else()
    target_compile_options(FilterManager PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add tests
add_executable(FilterManagerTests
    tests/FilterManagerTests.cpp
)

target_link_libraries(FilterManagerTests PRIVATE
    FilterManager
    Catch2::Catch2WithMain
)

target_include_directories(FilterManagerTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Register tests with CTest
include(CTest)
include(Catch)
catch_discover_tests(FilterManagerTests)
