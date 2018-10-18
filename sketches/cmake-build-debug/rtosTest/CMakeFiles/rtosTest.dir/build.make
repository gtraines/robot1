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
include rtosTest/CMakeFiles/rtosTest.dir/depend.make

# Include the progress variables for this target.
include rtosTest/CMakeFiles/rtosTest.dir/progress.make

# Include the compile flags for this target's objects.
include rtosTest/CMakeFiles/rtosTest.dir/flags.make

# Object files for target rtosTest
rtosTest_OBJECTS =

# External object files for target rtosTest
rtosTest_EXTERNAL_OBJECTS =

rtosTest/rtosTest: rtosTest/CMakeFiles/rtosTest.dir/build.make
rtosTest/rtosTest: libraries/Arduino_FreeRTOS/libArduino_FreeRTOS.a
rtosTest/rtosTest: libraries/TurretConfig/libTurretConfig.a
rtosTest/rtosTest: libraries/Indicator/libIndicator.a
rtosTest/rtosTest: libraries/CppList/libCppList.a
rtosTest/rtosTest: libraries/PotMotor/libPotMotor.a
rtosTest/rtosTest: libraries/TurretControllers/libTurretControllers.a
rtosTest/rtosTest: libraries/Arduino_FreeRTOS/libArduino_FreeRTOS.a
rtosTest/rtosTest: libraries/TurretConfig/libTurretConfig.a
rtosTest/rtosTest: libraries/Indicator/libIndicator.a
rtosTest/rtosTest: libraries/PotMotor/libPotMotor.a
rtosTest/rtosTest: libraries/CppList/libCppList.a
rtosTest/rtosTest: rtosTest/CMakeFiles/rtosTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX executable rtosTest"
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/rtosTest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtosTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rtosTest/CMakeFiles/rtosTest.dir/build: rtosTest/rtosTest

.PHONY : rtosTest/CMakeFiles/rtosTest.dir/build

rtosTest/CMakeFiles/rtosTest.dir/requires:

.PHONY : rtosTest/CMakeFiles/rtosTest.dir/requires

rtosTest/CMakeFiles/rtosTest.dir/clean:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug/rtosTest && $(CMAKE_COMMAND) -P CMakeFiles/rtosTest.dir/cmake_clean.cmake
.PHONY : rtosTest/CMakeFiles/rtosTest.dir/clean

rtosTest/CMakeFiles/rtosTest.dir/depend:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/Source/robot1/sketches /home/graham/Source/robot1/sketches/rtosTest /home/graham/Source/robot1/sketches/cmake-build-debug /home/graham/Source/robot1/sketches/cmake-build-debug/rtosTest /home/graham/Source/robot1/sketches/cmake-build-debug/rtosTest/CMakeFiles/rtosTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : rtosTest/CMakeFiles/rtosTest.dir/depend
