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
CMAKE_SOURCE_DIR = /home/graham/Source/robot1/sketches/libraries/TurretConfig

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TurretConfig.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TurretConfig.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TurretConfig.dir/flags.make

CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o: CMakeFiles/TurretConfig.dir/flags.make
CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o: ../TurretConfigPlacard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o -c /home/graham/Source/robot1/sketches/libraries/TurretConfig/TurretConfigPlacard.cpp

CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/TurretConfig/TurretConfigPlacard.cpp > CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.i

CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/TurretConfig/TurretConfigPlacard.cpp -o CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.s

CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.requires:

.PHONY : CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.requires

CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.provides: CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.requires
	$(MAKE) -f CMakeFiles/TurretConfig.dir/build.make CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.provides.build
.PHONY : CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.provides

CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.provides.build: CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o


CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o: CMakeFiles/TurretConfig.dir/flags.make
CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o: /home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o -c /home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp

CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp > CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.i

CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp -o CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.s

CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.requires:

.PHONY : CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.requires

CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.provides: CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.requires
	$(MAKE) -f CMakeFiles/TurretConfig.dir/build.make CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.provides.build
.PHONY : CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.provides

CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.provides.build: CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o


# Object files for target TurretConfig
TurretConfig_OBJECTS = \
"CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o" \
"CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o"

# External object files for target TurretConfig
TurretConfig_EXTERNAL_OBJECTS =

libTurretConfig.a: CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o
libTurretConfig.a: CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o
libTurretConfig.a: CMakeFiles/TurretConfig.dir/build.make
libTurretConfig.a: CMakeFiles/TurretConfig.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libTurretConfig.a"
	$(CMAKE_COMMAND) -P CMakeFiles/TurretConfig.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TurretConfig.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TurretConfig.dir/build: libTurretConfig.a

.PHONY : CMakeFiles/TurretConfig.dir/build

CMakeFiles/TurretConfig.dir/requires: CMakeFiles/TurretConfig.dir/TurretConfigPlacard.cpp.o.requires
CMakeFiles/TurretConfig.dir/requires: CMakeFiles/TurretConfig.dir/home/graham/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp.o.requires

.PHONY : CMakeFiles/TurretConfig.dir/requires

CMakeFiles/TurretConfig.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TurretConfig.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TurretConfig.dir/clean

CMakeFiles/TurretConfig.dir/depend:
	cd /home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/Source/robot1/sketches/libraries/TurretConfig /home/graham/Source/robot1/sketches/libraries/TurretConfig /home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug /home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug /home/graham/Source/robot1/sketches/libraries/TurretConfig/cmake-build-debug/CMakeFiles/TurretConfig.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TurretConfig.dir/depend
