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
CMAKE_SOURCE_DIR = "/home/vivek/programs/C++11 features/smart pointers/shared_ptr"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build"

# Include any dependencies generated for this target.
include CMakeFiles/sharedPointer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sharedPointer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sharedPointer.dir/flags.make

CMakeFiles/sharedPointer.dir/src/main.cpp.o: CMakeFiles/sharedPointer.dir/flags.make
CMakeFiles/sharedPointer.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sharedPointer.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sharedPointer.dir/src/main.cpp.o -c "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/src/main.cpp"

CMakeFiles/sharedPointer.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sharedPointer.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/src/main.cpp" > CMakeFiles/sharedPointer.dir/src/main.cpp.i

CMakeFiles/sharedPointer.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sharedPointer.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/src/main.cpp" -o CMakeFiles/sharedPointer.dir/src/main.cpp.s

# Object files for target sharedPointer
sharedPointer_OBJECTS = \
"CMakeFiles/sharedPointer.dir/src/main.cpp.o"

# External object files for target sharedPointer
sharedPointer_EXTERNAL_OBJECTS =

bin/sharedPointer: CMakeFiles/sharedPointer.dir/src/main.cpp.o
bin/sharedPointer: CMakeFiles/sharedPointer.dir/build.make
bin/sharedPointer: CMakeFiles/sharedPointer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/sharedPointer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sharedPointer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sharedPointer.dir/build: bin/sharedPointer

.PHONY : CMakeFiles/sharedPointer.dir/build

CMakeFiles/sharedPointer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sharedPointer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sharedPointer.dir/clean

CMakeFiles/sharedPointer.dir/depend:
	cd "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vivek/programs/C++11 features/smart pointers/shared_ptr" "/home/vivek/programs/C++11 features/smart pointers/shared_ptr" "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build" "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build" "/home/vivek/programs/C++11 features/smart pointers/shared_ptr/build/CMakeFiles/sharedPointer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/sharedPointer.dir/depend
