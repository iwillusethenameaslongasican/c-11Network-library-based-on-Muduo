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
include CMakeFiles/LogFileTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LogFileTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LogFileTest.dir/flags.make

CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o: ../Base/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o -c /home/c++code/NetwordLibrary/Base/ThreadPool.cpp

CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/ThreadPool.cpp > CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.i

CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/ThreadPool.cpp -o CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.s

CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o


CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o: ../Base/Condition.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o -c /home/c++code/NetwordLibrary/Base/Condition.cpp

CMakeFiles/LogFileTest.dir/Base/Condition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/Condition.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/Condition.cpp > CMakeFiles/LogFileTest.dir/Base/Condition.cpp.i

CMakeFiles/LogFileTest.dir/Base/Condition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/Condition.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/Condition.cpp -o CMakeFiles/LogFileTest.dir/Base/Condition.cpp.s

CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o


CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o: ../Base/CountDownLatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o -c /home/c++code/NetwordLibrary/Base/CountDownLatch.cpp

CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/CountDownLatch.cpp > CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.i

CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/CountDownLatch.cpp -o CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.s

CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o


CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o: ../Base/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o -c /home/c++code/NetwordLibrary/Base/Thread.cpp

CMakeFiles/LogFileTest.dir/Base/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/Thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/Thread.cpp > CMakeFiles/LogFileTest.dir/Base/Thread.cpp.i

CMakeFiles/LogFileTest.dir/Base/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/Thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/Thread.cpp -o CMakeFiles/LogFileTest.dir/Base/Thread.cpp.s

CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o


CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o: ../Base/TimeStamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o -c /home/c++code/NetwordLibrary/Base/TimeStamp.cpp

CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/TimeStamp.cpp > CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.i

CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/TimeStamp.cpp -o CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.s

CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o


CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o: ../Base/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o -c /home/c++code/NetwordLibrary/Base/Logger.cpp

CMakeFiles/LogFileTest.dir/Base/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/Logger.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/Logger.cpp > CMakeFiles/LogFileTest.dir/Base/Logger.cpp.i

CMakeFiles/LogFileTest.dir/Base/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/Logger.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/Logger.cpp -o CMakeFiles/LogFileTest.dir/Base/Logger.cpp.s

CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o


CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o: ../Base/LogStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o -c /home/c++code/NetwordLibrary/Base/LogStream.cpp

CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/LogStream.cpp > CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.i

CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/LogStream.cpp -o CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.s

CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o


CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o: ../Base/LogFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o -c /home/c++code/NetwordLibrary/Base/LogFile.cpp

CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/LogFile.cpp > CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.i

CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/LogFile.cpp -o CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.s

CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o


CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o: ../Base/FileUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o -c /home/c++code/NetwordLibrary/Base/FileUtil.cpp

CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/FileUtil.cpp > CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.i

CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/FileUtil.cpp -o CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.s

CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o


CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o: CMakeFiles/LogFileTest.dir/flags.make
CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o: ../Base/LogFileTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o -c /home/c++code/NetwordLibrary/Base/LogFileTest.cpp

CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c++code/NetwordLibrary/Base/LogFileTest.cpp > CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.i

CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c++code/NetwordLibrary/Base/LogFileTest.cpp -o CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.s

CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.requires:

.PHONY : CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.requires

CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.provides: CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/LogFileTest.dir/build.make CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.provides.build
.PHONY : CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.provides

CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.provides.build: CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o


# Object files for target LogFileTest
LogFileTest_OBJECTS = \
"CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o" \
"CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o"

# External object files for target LogFileTest
LogFileTest_EXTERNAL_OBJECTS =

LogFileTest: CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o
LogFileTest: CMakeFiles/LogFileTest.dir/build.make
LogFileTest: CMakeFiles/LogFileTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable LogFileTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LogFileTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LogFileTest.dir/build: LogFileTest

.PHONY : CMakeFiles/LogFileTest.dir/build

CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/ThreadPool.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/Condition.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/CountDownLatch.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/Thread.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/TimeStamp.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/Logger.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/LogStream.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/LogFile.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/FileUtil.cpp.o.requires
CMakeFiles/LogFileTest.dir/requires: CMakeFiles/LogFileTest.dir/Base/LogFileTest.cpp.o.requires

.PHONY : CMakeFiles/LogFileTest.dir/requires

CMakeFiles/LogFileTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LogFileTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LogFileTest.dir/clean

CMakeFiles/LogFileTest.dir/depend:
	cd /home/c++code/NetwordLibrary/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c++code/NetwordLibrary /home/c++code/NetwordLibrary /home/c++code/NetwordLibrary/cmake-build-debug /home/c++code/NetwordLibrary/cmake-build-debug /home/c++code/NetwordLibrary/cmake-build-debug/CMakeFiles/LogFileTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LogFileTest.dir/depend
