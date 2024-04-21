# Installation:
# mkdir build
# cd build
# cmake ..
# make

cmake_minimum_required(VERSION 3.10)
project(LRU8)

# Add the source files
set(SOURCES
    lru8.h
    test_lru8.cpp
)

# Set the target executable
add_executable(test_lru8 ${SOURCES})

# Set C++ standard to C++11
target_compile_features(test_lru8 PRIVATE cxx_std_11)

# Check for the operating system and adjust include directories accordingly
if (WIN32)
    # Windows-specific settings
    message(STATUS "Configuring for Windows")
else()
    # Unix-specific settings
    message(STATUS "Configuring for Unix")

    # Check if we are using GCC
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        # For Unix systems using GCC, add the required include directories
        target_include_directories(test_lru8 PRIVATE "/usr/local/include")
    endif()
endif()

