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
CMAKE_SOURCE_DIR = /home/vivek/matic/shell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vivek/matic/shell/build

# Include any dependencies generated for this target.
include src/CMakeFiles/shell.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/shell.dir/flags.make

src/CMakeFiles/shell.dir/main.cpp.o: src/CMakeFiles/shell.dir/flags.make
src/CMakeFiles/shell.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vivek/matic/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/shell.dir/main.cpp.o"
	cd /home/vivek/matic/shell/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell.dir/main.cpp.o -c /home/vivek/matic/shell/src/main.cpp

src/CMakeFiles/shell.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell.dir/main.cpp.i"
	cd /home/vivek/matic/shell/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vivek/matic/shell/src/main.cpp > CMakeFiles/shell.dir/main.cpp.i

src/CMakeFiles/shell.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell.dir/main.cpp.s"
	cd /home/vivek/matic/shell/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vivek/matic/shell/src/main.cpp -o CMakeFiles/shell.dir/main.cpp.s

src/CMakeFiles/shell.dir/Shell.cpp.o: src/CMakeFiles/shell.dir/flags.make
src/CMakeFiles/shell.dir/Shell.cpp.o: ../src/Shell.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vivek/matic/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/shell.dir/Shell.cpp.o"
	cd /home/vivek/matic/shell/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shell.dir/Shell.cpp.o -c /home/vivek/matic/shell/src/Shell.cpp

src/CMakeFiles/shell.dir/Shell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shell.dir/Shell.cpp.i"
	cd /home/vivek/matic/shell/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vivek/matic/shell/src/Shell.cpp > CMakeFiles/shell.dir/Shell.cpp.i

src/CMakeFiles/shell.dir/Shell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shell.dir/Shell.cpp.s"
	cd /home/vivek/matic/shell/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vivek/matic/shell/src/Shell.cpp -o CMakeFiles/shell.dir/Shell.cpp.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/main.cpp.o" \
"CMakeFiles/shell.dir/Shell.cpp.o"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

../bin/shell: src/CMakeFiles/shell.dir/main.cpp.o
../bin/shell: src/CMakeFiles/shell.dir/Shell.cpp.o
../bin/shell: src/CMakeFiles/shell.dir/build.make
../bin/shell: src/CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vivek/matic/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/shell"
	cd /home/vivek/matic/shell/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/shell.dir/build: ../bin/shell

.PHONY : src/CMakeFiles/shell.dir/build

src/CMakeFiles/shell.dir/clean:
	cd /home/vivek/matic/shell/build/src && $(CMAKE_COMMAND) -P CMakeFiles/shell.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/shell.dir/clean

src/CMakeFiles/shell.dir/depend:
	cd /home/vivek/matic/shell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vivek/matic/shell /home/vivek/matic/shell/src /home/vivek/matic/shell/build /home/vivek/matic/shell/build/src /home/vivek/matic/shell/build/src/CMakeFiles/shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/shell.dir/depend

