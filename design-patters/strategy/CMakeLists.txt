cmake_minimum_required(VERSION 3.12)  # Minimum CMake version required

project(MyProject)  # Name your project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the sources for your project
set(SOURCES
    src/main.cpp
#   lib/mylib.cpp
)

# Include directories
include_directories(inc)

# Set the binary output directory to a "bin" directory within the project
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create an executable from the sources
add_executable(strategyPattern ${SOURCES})

