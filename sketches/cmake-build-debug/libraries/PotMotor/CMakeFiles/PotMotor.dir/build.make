# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/graham/clion2018/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/graham/clion2018/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/graham/Source/robot1/sketches

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/graham/Source/robot1/sketches/cmake-build-debug

# Include any dependencies generated for this target.
include libraries/PotMotor/CMakeFiles/PotMotor.dir/depend.make

# Include the progress variables for this target.
include libraries/PotMotor/CMakeFiles/PotMotor.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/PotMotor/CMakeFiles/PotMotor.dir/flags.make

libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj: libraries/PotMotor/CMakeFiles/PotMotor.dir/flags.make
libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj: ../libraries/PotMotor/PotMotor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor && /usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PotMotor.dir/PotMotor.cpp.obj -c /home/graham/Source/robot1/sketches/libraries/PotMotor/PotMotor.cpp

libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PotMotor.dir/PotMotor.cpp.i"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor && /usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/PotMotor/PotMotor.cpp > CMakeFiles/PotMotor.dir/PotMotor.cpp.i

libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PotMotor.dir/PotMotor.cpp.s"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor && /usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/PotMotor/PotMotor.cpp -o CMakeFiles/PotMotor.dir/PotMotor.cpp.s

libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.requires:

.PHONY : libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.requires

libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.provides: libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.requires
	$(MAKE) -f libraries/PotMotor/CMakeFiles/PotMotor.dir/build.make libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.provides.build
.PHONY : libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.provides

libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.provides.build: libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj


# Object files for target PotMotor
PotMotor_OBJECTS = \
"CMakeFiles/PotMotor.dir/PotMotor.cpp.obj"

# External object files for target PotMotor
PotMotor_EXTERNAL_OBJECTS =

libraries/PotMotor/libPotMotor.a: libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj
libraries/PotMotor/libPotMotor.a: libraries/PotMotor/CMakeFiles/PotMotor.dir/build.make
libraries/PotMotor/libPotMotor.a: libraries/PotMotor/CMakeFiles/PotMotor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libPotMotor.a"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor && $(CMAKE_COMMAND) -P CMakeFiles/PotMotor.dir/cmake_clean_target.cmake
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PotMotor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/PotMotor/CMakeFiles/PotMotor.dir/build: libraries/PotMotor/libPotMotor.a

.PHONY : libraries/PotMotor/CMakeFiles/PotMotor.dir/build

libraries/PotMotor/CMakeFiles/PotMotor.dir/requires: libraries/PotMotor/CMakeFiles/PotMotor.dir/PotMotor.cpp.obj.requires

.PHONY : libraries/PotMotor/CMakeFiles/PotMotor.dir/requires

libraries/PotMotor/CMakeFiles/PotMotor.dir/clean:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor && $(CMAKE_COMMAND) -P CMakeFiles/PotMotor.dir/cmake_clean.cmake
.PHONY : libraries/PotMotor/CMakeFiles/PotMotor.dir/clean

libraries/PotMotor/CMakeFiles/PotMotor.dir/depend:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/Source/robot1/sketches /home/graham/Source/robot1/sketches/libraries/PotMotor /home/graham/Source/robot1/sketches/cmake-build-debug /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor/CMakeFiles/PotMotor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/PotMotor/CMakeFiles/PotMotor.dir/depend
