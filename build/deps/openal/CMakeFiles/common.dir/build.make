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
include deps/openal/CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include deps/openal/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include deps/openal/CMakeFiles/common.dir/flags.make

deps/openal/CMakeFiles/common.dir/common/atomic.c.o: deps/openal/CMakeFiles/common.dir/flags.make
deps/openal/CMakeFiles/common.dir/common/atomic.c.o: ../deps/openal/common/atomic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object deps/openal/CMakeFiles/common.dir/common/atomic.c.o"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/atomic.c.o   -c /home/vlad/Dev/simple/deps/openal/common/atomic.c

deps/openal/CMakeFiles/common.dir/common/atomic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/atomic.c.i"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vlad/Dev/simple/deps/openal/common/atomic.c > CMakeFiles/common.dir/common/atomic.c.i

deps/openal/CMakeFiles/common.dir/common/atomic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/atomic.c.s"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vlad/Dev/simple/deps/openal/common/atomic.c -o CMakeFiles/common.dir/common/atomic.c.s

deps/openal/CMakeFiles/common.dir/common/atomic.c.o.requires:

.PHONY : deps/openal/CMakeFiles/common.dir/common/atomic.c.o.requires

deps/openal/CMakeFiles/common.dir/common/atomic.c.o.provides: deps/openal/CMakeFiles/common.dir/common/atomic.c.o.requires
	$(MAKE) -f deps/openal/CMakeFiles/common.dir/build.make deps/openal/CMakeFiles/common.dir/common/atomic.c.o.provides.build
.PHONY : deps/openal/CMakeFiles/common.dir/common/atomic.c.o.provides

deps/openal/CMakeFiles/common.dir/common/atomic.c.o.provides.build: deps/openal/CMakeFiles/common.dir/common/atomic.c.o


deps/openal/CMakeFiles/common.dir/common/rwlock.c.o: deps/openal/CMakeFiles/common.dir/flags.make
deps/openal/CMakeFiles/common.dir/common/rwlock.c.o: ../deps/openal/common/rwlock.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object deps/openal/CMakeFiles/common.dir/common/rwlock.c.o"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/rwlock.c.o   -c /home/vlad/Dev/simple/deps/openal/common/rwlock.c

deps/openal/CMakeFiles/common.dir/common/rwlock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/rwlock.c.i"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vlad/Dev/simple/deps/openal/common/rwlock.c > CMakeFiles/common.dir/common/rwlock.c.i

deps/openal/CMakeFiles/common.dir/common/rwlock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/rwlock.c.s"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vlad/Dev/simple/deps/openal/common/rwlock.c -o CMakeFiles/common.dir/common/rwlock.c.s

deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.requires:

.PHONY : deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.requires

deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.provides: deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.requires
	$(MAKE) -f deps/openal/CMakeFiles/common.dir/build.make deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.provides.build
.PHONY : deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.provides

deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.provides.build: deps/openal/CMakeFiles/common.dir/common/rwlock.c.o


deps/openal/CMakeFiles/common.dir/common/threads.c.o: deps/openal/CMakeFiles/common.dir/flags.make
deps/openal/CMakeFiles/common.dir/common/threads.c.o: ../deps/openal/common/threads.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object deps/openal/CMakeFiles/common.dir/common/threads.c.o"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/threads.c.o   -c /home/vlad/Dev/simple/deps/openal/common/threads.c

deps/openal/CMakeFiles/common.dir/common/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/threads.c.i"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vlad/Dev/simple/deps/openal/common/threads.c > CMakeFiles/common.dir/common/threads.c.i

deps/openal/CMakeFiles/common.dir/common/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/threads.c.s"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vlad/Dev/simple/deps/openal/common/threads.c -o CMakeFiles/common.dir/common/threads.c.s

deps/openal/CMakeFiles/common.dir/common/threads.c.o.requires:

.PHONY : deps/openal/CMakeFiles/common.dir/common/threads.c.o.requires

deps/openal/CMakeFiles/common.dir/common/threads.c.o.provides: deps/openal/CMakeFiles/common.dir/common/threads.c.o.requires
	$(MAKE) -f deps/openal/CMakeFiles/common.dir/build.make deps/openal/CMakeFiles/common.dir/common/threads.c.o.provides.build
.PHONY : deps/openal/CMakeFiles/common.dir/common/threads.c.o.provides

deps/openal/CMakeFiles/common.dir/common/threads.c.o.provides.build: deps/openal/CMakeFiles/common.dir/common/threads.c.o


deps/openal/CMakeFiles/common.dir/common/uintmap.c.o: deps/openal/CMakeFiles/common.dir/flags.make
deps/openal/CMakeFiles/common.dir/common/uintmap.c.o: ../deps/openal/common/uintmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object deps/openal/CMakeFiles/common.dir/common/uintmap.c.o"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/common.dir/common/uintmap.c.o   -c /home/vlad/Dev/simple/deps/openal/common/uintmap.c

deps/openal/CMakeFiles/common.dir/common/uintmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/common/uintmap.c.i"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/vlad/Dev/simple/deps/openal/common/uintmap.c > CMakeFiles/common.dir/common/uintmap.c.i

deps/openal/CMakeFiles/common.dir/common/uintmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/common/uintmap.c.s"
	cd /home/vlad/Dev/simple/build/deps/openal && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/vlad/Dev/simple/deps/openal/common/uintmap.c -o CMakeFiles/common.dir/common/uintmap.c.s

deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.requires:

.PHONY : deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.requires

deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.provides: deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.requires
	$(MAKE) -f deps/openal/CMakeFiles/common.dir/build.make deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.provides.build
.PHONY : deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.provides

deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.provides.build: deps/openal/CMakeFiles/common.dir/common/uintmap.c.o


# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/common/atomic.c.o" \
"CMakeFiles/common.dir/common/rwlock.c.o" \
"CMakeFiles/common.dir/common/threads.c.o" \
"CMakeFiles/common.dir/common/uintmap.c.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

deps/openal/libcommon.a: deps/openal/CMakeFiles/common.dir/common/atomic.c.o
deps/openal/libcommon.a: deps/openal/CMakeFiles/common.dir/common/rwlock.c.o
deps/openal/libcommon.a: deps/openal/CMakeFiles/common.dir/common/threads.c.o
deps/openal/libcommon.a: deps/openal/CMakeFiles/common.dir/common/uintmap.c.o
deps/openal/libcommon.a: deps/openal/CMakeFiles/common.dir/build.make
deps/openal/libcommon.a: deps/openal/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vlad/Dev/simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libcommon.a"
	cd /home/vlad/Dev/simple/build/deps/openal && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	cd /home/vlad/Dev/simple/build/deps/openal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/openal/CMakeFiles/common.dir/build: deps/openal/libcommon.a

.PHONY : deps/openal/CMakeFiles/common.dir/build

deps/openal/CMakeFiles/common.dir/requires: deps/openal/CMakeFiles/common.dir/common/atomic.c.o.requires
deps/openal/CMakeFiles/common.dir/requires: deps/openal/CMakeFiles/common.dir/common/rwlock.c.o.requires
deps/openal/CMakeFiles/common.dir/requires: deps/openal/CMakeFiles/common.dir/common/threads.c.o.requires
deps/openal/CMakeFiles/common.dir/requires: deps/openal/CMakeFiles/common.dir/common/uintmap.c.o.requires

.PHONY : deps/openal/CMakeFiles/common.dir/requires

deps/openal/CMakeFiles/common.dir/clean:
	cd /home/vlad/Dev/simple/build/deps/openal && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : deps/openal/CMakeFiles/common.dir/clean

deps/openal/CMakeFiles/common.dir/depend:
	cd /home/vlad/Dev/simple/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vlad/Dev/simple /home/vlad/Dev/simple/deps/openal /home/vlad/Dev/simple/build /home/vlad/Dev/simple/build/deps/openal /home/vlad/Dev/simple/build/deps/openal/CMakeFiles/common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/openal/CMakeFiles/common.dir/depend
