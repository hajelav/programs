cmake_minimum_required(VERSION 3.10)
project(Shell)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add strict compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    # For Clang and GCC
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# Add the subdirectories
add_subdirectory(src)