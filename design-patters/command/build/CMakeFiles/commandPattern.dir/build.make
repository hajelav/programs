# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vivek/programs/design-patters/command

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vivek/programs/design-patters/command/build

# Include any dependencies generated for this target.
include CMakeFiles/commandPattern.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/commandPattern.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/commandPattern.dir/flags.make

CMakeFiles/commandPattern.dir/src/main.cpp.o: CMakeFiles/commandPattern.dir/flags.make
CMakeFiles/commandPattern.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vivek/programs/design-patters/command/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/commandPattern.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/commandPattern.dir/src/main.cpp.o -c /home/vivek/programs/design-patters/command/src/main.cpp

CMakeFiles/commandPattern.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/commandPattern.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vivek/programs/design-patters/command/src/main.cpp > CMakeFiles/commandPattern.dir/src/main.cpp.i

CMakeFiles/commandPattern.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/commandPattern.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vivek/programs/design-patters/command/src/main.cpp -o CMakeFiles/commandPattern.dir/src/main.cpp.s

# Object files for target commandPattern
commandPattern_OBJECTS = \
"CMakeFiles/commandPattern.dir/src/main.cpp.o"

# External object files for target commandPattern
commandPattern_EXTERNAL_OBJECTS =

bin/commandPattern: CMakeFiles/commandPattern.dir/src/main.cpp.o
bin/commandPattern: CMakeFiles/commandPattern.dir/build.make
bin/commandPattern: CMakeFiles/commandPattern.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vivek/programs/design-patters/command/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/commandPattern"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/commandPattern.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/commandPattern.dir/build: bin/commandPattern

.PHONY : CMakeFiles/commandPattern.dir/build

CMakeFiles/commandPattern.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/commandPattern.dir/cmake_clean.cmake
.PHONY : CMakeFiles/commandPattern.dir/clean

CMakeFiles/commandPattern.dir/depend:
	cd /home/vivek/programs/design-patters/command/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vivek/programs/design-patters/command /home/vivek/programs/design-patters/command /home/vivek/programs/design-patters/command/build /home/vivek/programs/design-patters/command/build /home/vivek/programs/design-patters/command/build/CMakeFiles/commandPattern.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/commandPattern.dir/depend

