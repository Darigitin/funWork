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
CMAKE_COMMAND = /cygdrive/c/Users/Matt/.CLion2016.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Matt/.CLion2016.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Assignment_5Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Assignment_5Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assignment_5Server.dir/flags.make

CMakeFiles/Assignment_5Server.dir/main.c.o: CMakeFiles/Assignment_5Server.dir/flags.make
CMakeFiles/Assignment_5Server.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Assignment_5Server.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Assignment_5Server.dir/main.c.o   -c /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/main.c

CMakeFiles/Assignment_5Server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Assignment_5Server.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/main.c > CMakeFiles/Assignment_5Server.dir/main.c.i

CMakeFiles/Assignment_5Server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Assignment_5Server.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/main.c -o CMakeFiles/Assignment_5Server.dir/main.c.s

CMakeFiles/Assignment_5Server.dir/main.c.o.requires:

.PHONY : CMakeFiles/Assignment_5Server.dir/main.c.o.requires

CMakeFiles/Assignment_5Server.dir/main.c.o.provides: CMakeFiles/Assignment_5Server.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Assignment_5Server.dir/build.make CMakeFiles/Assignment_5Server.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Assignment_5Server.dir/main.c.o.provides

CMakeFiles/Assignment_5Server.dir/main.c.o.provides.build: CMakeFiles/Assignment_5Server.dir/main.c.o


# Object files for target Assignment_5Server
Assignment_5Server_OBJECTS = \
"CMakeFiles/Assignment_5Server.dir/main.c.o"

# External object files for target Assignment_5Server
Assignment_5Server_EXTERNAL_OBJECTS =

Assignment_5Server.exe: CMakeFiles/Assignment_5Server.dir/main.c.o
Assignment_5Server.exe: CMakeFiles/Assignment_5Server.dir/build.make
Assignment_5Server.exe: CMakeFiles/Assignment_5Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Assignment_5Server.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assignment_5Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assignment_5Server.dir/build: Assignment_5Server.exe

.PHONY : CMakeFiles/Assignment_5Server.dir/build

CMakeFiles/Assignment_5Server.dir/requires: CMakeFiles/Assignment_5Server.dir/main.c.o.requires

.PHONY : CMakeFiles/Assignment_5Server.dir/requires

CMakeFiles/Assignment_5Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Assignment_5Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Assignment_5Server.dir/clean

CMakeFiles/Assignment_5Server.dir/depend:
	cd /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3 /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3 /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug /cygdrive/c/Users/Matt/Documents/Projects/funWork/mikeSP2017/Assignment_5Server3/cmake-build-debug/CMakeFiles/Assignment_5Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Assignment_5Server.dir/depend

