# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/jackson/software/clion-2016.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jackson/software/clion-2016.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/c++code/NetwordLibrary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/c++code/NetwordLibrary/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/testThread.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testThread.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testThread.dir/flags.make

CMakeFiles/testThread.dir/Base/Thread.cpp.o: CMakeFiles/testThread.dir/flags.make
CMakeFiles/testThread.dir/Base/Thread.cpp.o: ../Base/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testThread.dir/Base/Thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testThread.dir/Base/Thread.cpp.o -c /home/c++code/NetwordLibrary/Base/Thread.cpp

CMakeFiles/testThread.dir/Base/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testThread.dir/Base/Thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/Thread.cpp > CMakeFiles/testThread.dir/Base/Thread.cpp.i

CMakeFiles/testThread.dir/Base/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testThread.dir/Base/Thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/Thread.cpp -o CMakeFiles/testThread.dir/Base/Thread.cpp.s

CMakeFiles/testThread.dir/Base/Thread.cpp.o.requires:

.PHONY : CMakeFiles/testThread.dir/Base/Thread.cpp.o.requires

CMakeFiles/testThread.dir/Base/Thread.cpp.o.provides: CMakeFiles/testThread.dir/Base/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/testThread.dir/build.make CMakeFiles/testThread.dir/Base/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/testThread.dir/Base/Thread.cpp.o.provides

CMakeFiles/testThread.dir/Base/Thread.cpp.o.provides.build: CMakeFiles/testThread.dir/Base/Thread.cpp.o


CMakeFiles/testThread.dir/Base/testThread.cpp.o: CMakeFiles/testThread.dir/flags.make
CMakeFiles/testThread.dir/Base/testThread.cpp.o: ../Base/testThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testThread.dir/Base/testThread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testThread.dir/Base/testThread.cpp.o -c /home/c++code/NetwordLibrary/Base/testThread.cpp

CMakeFiles/testThread.dir/Base/testThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testThread.dir/Base/testThread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/testThread.cpp > CMakeFiles/testThread.dir/Base/testThread.cpp.i

CMakeFiles/testThread.dir/Base/testThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testThread.dir/Base/testThread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/testThread.cpp -o CMakeFiles/testThread.dir/Base/testThread.cpp.s

CMakeFiles/testThread.dir/Base/testThread.cpp.o.requires:

.PHONY : CMakeFiles/testThread.dir/Base/testThread.cpp.o.requires

CMakeFiles/testThread.dir/Base/testThread.cpp.o.provides: CMakeFiles/testThread.dir/Base/testThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/testThread.dir/build.make CMakeFiles/testThread.dir/Base/testThread.cpp.o.provides.build
.PHONY : CMakeFiles/testThread.dir/Base/testThread.cpp.o.provides

CMakeFiles/testThread.dir/Base/testThread.cpp.o.provides.build: CMakeFiles/testThread.dir/Base/testThread.cpp.o


# Object files for target testThread
testThread_OBJECTS = \
"CMakeFiles/testThread.dir/Base/Thread.cpp.o" \
"CMakeFiles/testThread.dir/Base/testThread.cpp.o"

# External object files for target testThread
testThread_EXTERNAL_OBJECTS =

testThread: CMakeFiles/testThread.dir/Base/Thread.cpp.o
testThread: CMakeFiles/testThread.dir/Base/testThread.cpp.o
testThread: CMakeFiles/testThread.dir/build.make
testThread: CMakeFiles/testThread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testThread"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testThread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testThread.dir/build: testThread

.PHONY : CMakeFiles/testThread.dir/build

CMakeFiles/testThread.dir/requires: CMakeFiles/testThread.dir/Base/Thread.cpp.o.requires
CMakeFiles/testThread.dir/requires: CMakeFiles/testThread.dir/Base/testThread.cpp.o.requires

.PHONY : CMakeFiles/testThread.dir/requires

CMakeFiles/testThread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testThread.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testThread.dir/clean

CMakeFiles/testThread.dir/depend:
	cd /home/c++code/NetwordLibrary/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c++code/NetwordLibrary /home/c++code/NetwordLibrary /home/c++code/NetwordLibrary/cmake-build-debug /home/c++code/NetwordLibrary/cmake-build-debug /home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles/testThread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testThread.dir/depend

