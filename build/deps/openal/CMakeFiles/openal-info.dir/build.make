# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_SOURCE_DIR = /home/vlad/Dev/simple

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vlad/Dev/simple/build

# Include any dependencies generated for this target.
include deps/openal/CMakeFiles/openal-info.dir/depend.make

# Include the progress variables for this target.
include deps/openal/CMakeFiles/openal-info.dir/progress.make

# Include the compile flags for this target's objects.
include deps/openal/CMakeFiles/openal-info.dir/flags.make

deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o: deps/openal/CMakeFiles/openal-info.dir/flags.make
deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o: ../deps/openal/utils/openal-info.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/openal-info.dir/utils/openal-info.c.o   -c /home/vlad/Dev/simple/deps/openal/utils/openal-info.c

deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openal-info.dir/utils/openal-info.c.i"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vlad/Dev/simple/deps/openal/utils/openal-info.c > CMakeFiles/openal-info.dir/utils/openal-info.c.i

deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openal-info.dir/utils/openal-info.c.s"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vlad/Dev/simple/deps/openal/utils/openal-info.c -o CMakeFiles/openal-info.dir/utils/openal-info.c.s

deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.requires:

.PHONY : deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.requires

deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.provides: deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.requires
	$(MAKE) -f deps/openal/CMakeFiles/openal-info.dir/build.make deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.provides.build
.PHONY : deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.provides

deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.provides.build: deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o


# Object files for target openal-info
openal__info_OBJECTS = \
"CMakeFiles/openal-info.dir/utils/openal-info.c.o"

# External object files for target openal-info
openal__info_EXTERNAL_OBJECTS =

deps/openal/openal-info: deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o
deps/openal/openal-info: deps/openal/CMakeFiles/openal-info.dir/build.make
deps/openal/openal-info: deps/openal/libopenal.so.1.15.1
deps/openal/openal-info: deps/openal/libcommon.a
deps/openal/openal-info: /usr/lib64/libfluidsynth.so
deps/openal/openal-info: deps/openal/CMakeFiles/openal-info.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable openal-info"
	cd /home/vlad/Dev/simple/build/deps/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/openal-info.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/openal/CMakeFiles/openal-info.dir/build: deps/openal/openal-info

.PHONY : deps/openal/CMakeFiles/openal-info.dir/build

deps/openal/CMakeFiles/openal-info.dir/requires: deps/openal/CMakeFiles/openal-info.dir/utils/openal-info.c.o.requires

.PHONY : deps/openal/CMakeFiles/openal-info.dir/requires

deps/openal/CMakeFiles/openal-info.dir/clean:
	cd /home/vlad/Dev/simple/build/deps/openal && $(CMAKE_COMMAND) -P CMakeFiles/openal-info.dir/cmake_clean.cmake
.PHONY : deps/openal/CMakeFiles/openal-info.dir/clean

deps/openal/CMakeFiles/openal-info.dir/depend:
	cd /home/vlad/Dev/simple/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vlad/Dev/simple /home/vlad/Dev/simple/deps/openal /home/vlad/Dev/simple/build /home/vlad/Dev/simple/build/deps/openal /home/vlad/Dev/simple/build/deps/openal/CMakeFiles/openal-info.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/openal/CMakeFiles/openal-info.dir/depend
