# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/nvidia/pba_g2o_compare/g2o_ba

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nvidia/pba_g2o_compare/g2o_ba/build

# Include any dependencies generated for this target.
include CMakeFiles/g2o_ba.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/g2o_ba.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/g2o_ba.dir/flags.make

CMakeFiles/g2o_ba.dir/src/main.cc.o: CMakeFiles/g2o_ba.dir/flags.make
CMakeFiles/g2o_ba.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nvidia/pba_g2o_compare/g2o_ba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/g2o_ba.dir/src/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g2o_ba.dir/src/main.cc.o -c /home/nvidia/pba_g2o_compare/g2o_ba/src/main.cc

CMakeFiles/g2o_ba.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g2o_ba.dir/src/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nvidia/pba_g2o_compare/g2o_ba/src/main.cc > CMakeFiles/g2o_ba.dir/src/main.cc.i

CMakeFiles/g2o_ba.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g2o_ba.dir/src/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nvidia/pba_g2o_compare/g2o_ba/src/main.cc -o CMakeFiles/g2o_ba.dir/src/main.cc.s

CMakeFiles/g2o_ba.dir/src/main.cc.o.requires:

.PHONY : CMakeFiles/g2o_ba.dir/src/main.cc.o.requires

CMakeFiles/g2o_ba.dir/src/main.cc.o.provides: CMakeFiles/g2o_ba.dir/src/main.cc.o.requires
	$(MAKE) -f CMakeFiles/g2o_ba.dir/build.make CMakeFiles/g2o_ba.dir/src/main.cc.o.provides.build
.PHONY : CMakeFiles/g2o_ba.dir/src/main.cc.o.provides

CMakeFiles/g2o_ba.dir/src/main.cc.o.provides.build: CMakeFiles/g2o_ba.dir/src/main.cc.o


# Object files for target g2o_ba
g2o_ba_OBJECTS = \
"CMakeFiles/g2o_ba.dir/src/main.cc.o"

# External object files for target g2o_ba
g2o_ba_EXTERNAL_OBJECTS =

../bin/g2o_ba: CMakeFiles/g2o_ba.dir/src/main.cc.o
../bin/g2o_ba: CMakeFiles/g2o_ba.dir/build.make
../bin/g2o_ba: CMakeFiles/g2o_ba.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nvidia/pba_g2o_compare/g2o_ba/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/g2o_ba"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g2o_ba.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/g2o_ba.dir/build: ../bin/g2o_ba

.PHONY : CMakeFiles/g2o_ba.dir/build

CMakeFiles/g2o_ba.dir/requires: CMakeFiles/g2o_ba.dir/src/main.cc.o.requires

.PHONY : CMakeFiles/g2o_ba.dir/requires

CMakeFiles/g2o_ba.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/g2o_ba.dir/cmake_clean.cmake
.PHONY : CMakeFiles/g2o_ba.dir/clean

CMakeFiles/g2o_ba.dir/depend:
	cd /home/nvidia/pba_g2o_compare/g2o_ba/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nvidia/pba_g2o_compare/g2o_ba /home/nvidia/pba_g2o_compare/g2o_ba /home/nvidia/pba_g2o_compare/g2o_ba/build /home/nvidia/pba_g2o_compare/g2o_ba/build /home/nvidia/pba_g2o_compare/g2o_ba/build/CMakeFiles/g2o_ba.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/g2o_ba.dir/depend
