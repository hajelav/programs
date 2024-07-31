# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)

# Source files
set(SOURCES 
main.cpp
Shell.cpp
)
add_executable(shell ${SOURCES})
# Set output directories for object files
set_target_properties(shell PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
)


