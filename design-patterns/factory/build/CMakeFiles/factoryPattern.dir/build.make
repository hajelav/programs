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
CMAKE_SOURCE_DIR = /home/vivek/programs/design-patterns/factory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vivek/programs/design-patterns/factory/build

# Include any dependencies generated for this target.
include CMakeFiles/factoryPattern.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/factoryPattern.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/factoryPattern.dir/flags.make

CMakeFiles/factoryPattern.dir/src/main.cpp.o: CMakeFiles/factoryPattern.dir/flags.make
CMakeFiles/factoryPattern.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vivek/programs/design-patterns/factory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/factoryPattern.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/factoryPattern.dir/src/main.cpp.o -c /home/vivek/programs/design-patterns/factory/src/main.cpp

CMakeFiles/factoryPattern.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/factoryPattern.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vivek/programs/design-patterns/factory/src/main.cpp > CMakeFiles/factoryPattern.dir/src/main.cpp.i

CMakeFiles/factoryPattern.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/factoryPattern.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vivek/programs/design-patterns/factory/src/main.cpp -o CMakeFiles/factoryPattern.dir/src/main.cpp.s

# Object files for target factoryPattern
factoryPattern_OBJECTS = \
"CMakeFiles/factoryPattern.dir/src/main.cpp.o"

# External object files for target factoryPattern
factoryPattern_EXTERNAL_OBJECTS =

bin/factoryPattern: CMakeFiles/factoryPattern.dir/src/main.cpp.o
bin/factoryPattern: CMakeFiles/factoryPattern.dir/build.make
bin/factoryPattern: CMakeFiles/factoryPattern.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vivek/programs/design-patterns/factory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/factoryPattern"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/factoryPattern.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/factoryPattern.dir/build: bin/factoryPattern

.PHONY : CMakeFiles/factoryPattern.dir/build

CMakeFiles/factoryPattern.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/factoryPattern.dir/cmake_clean.cmake
.PHONY : CMakeFiles/factoryPattern.dir/clean

CMakeFiles/factoryPattern.dir/depend:
	cd /home/vivek/programs/design-patterns/factory/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vivek/programs/design-patterns/factory /home/vivek/programs/design-patterns/factory /home/vivek/programs/design-patterns/factory/build /home/vivek/programs/design-patterns/factory/build /home/vivek/programs/design-patterns/factory/build/CMakeFiles/factoryPattern.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/factoryPattern.dir/depend

