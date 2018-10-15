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
include libraries/TurretConfig/CMakeFiles/TurretConfig.dir/depend.make

# Include the progress variables for this target.
include libraries/TurretConfig/CMakeFiles/TurretConfig.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/TurretConfig/CMakeFiles/TurretConfig.dir/flags.make

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/flags.make
libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj: ../libraries/TurretConfig/TurretConfigPlacard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig && /usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj -c /home/graham/Source/robot1/sketches/libraries/TurretConfig/TurretConfigPlacard.cpp

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.i"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig && /usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/TurretConfig/TurretConfigPlacard.cpp > CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.i

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.s"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig && /usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/TurretConfig/TurretConfigPlacard.cpp -o CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.s

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.requires:

.PHONY : libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.requires

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.provides: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.requires
	$(MAKE) -f libraries/TurretConfig/CMakeFiles/TurretConfig.dir/build.make libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.provides.build
.PHONY : libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.provides

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.provides.build: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj


# Object files for target TurretConfig
TurretConfig_OBJECTS = \
"CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj"

# External object files for target TurretConfig
TurretConfig_EXTERNAL_OBJECTS =

libraries/TurretConfig/libTurretConfig.a: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj
libraries/TurretConfig/libTurretConfig.a: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/build.make
libraries/TurretConfig/libTurretConfig.a: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libTurretConfig.a"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig && $(CMAKE_COMMAND) -P CMakeFiles/TurretConfig.dir/cmake_clean_target.cmake
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TurretConfig.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/TurretConfig/CMakeFiles/TurretConfig.dir/build: libraries/TurretConfig/libTurretConfig.a

.PHONY : libraries/TurretConfig/CMakeFiles/TurretConfig.dir/build

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/requires: libraries/TurretConfig/CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.obj.requires

.PHONY : libraries/TurretConfig/CMakeFiles/TurretConfig.dir/requires

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/clean:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig && $(CMAKE_COMMAND) -P CMakeFiles/TurretConfig.dir/cmake_clean.cmake
.PHONY : libraries/TurretConfig/CMakeFiles/TurretConfig.dir/clean

libraries/TurretConfig/CMakeFiles/TurretConfig.dir/depend:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/Source/robot1/sketches /home/graham/Source/robot1/sketches/libraries/TurretConfig /home/graham/Source/robot1/sketches/cmake-build-debug /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig /home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig/CMakeFiles/TurretConfig.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/TurretConfig/CMakeFiles/TurretConfig.dir/depend

