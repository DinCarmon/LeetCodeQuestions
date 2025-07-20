cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Median4)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Median4 main.cpp)

# Enable strict compilation warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Median4 PRIVATE -Wall -Wextra -Wpedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Median4 PRIVATE /W4 /WX)
endif()