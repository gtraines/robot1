# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/graham/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/graham/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/graham/projects/robot1/cpp/SpeedControl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SpeedControl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SpeedControl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SpeedControl.dir/flags.make

SpeedControl_test_harness.ino.cpp: ../test_harness.ino
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Regnerating test_harness.ino Sketch"
	/home/graham/clion/bin/cmake/bin/cmake /home/graham/projects/robot1/cpp/SpeedControl

CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj: CMakeFiles/SpeedControl.dir/flags.make
CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj: SpeedControl_test_harness.ino.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj"
	/usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj -c /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl_test_harness.ino.cpp

CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl_test_harness.ino.cpp > CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.i

CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl_test_harness.ino.cpp -o CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.s

CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.requires:

.PHONY : CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.requires

CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.provides: CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.requires
	$(MAKE) -f CMakeFiles/SpeedControl.dir/build.make CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.provides.build
.PHONY : CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.provides

CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.provides.build: CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj


# Object files for target SpeedControl
SpeedControl_OBJECTS = \
"CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj"

# External object files for target SpeedControl
SpeedControl_EXTERNAL_OBJECTS =

SpeedControl.elf: CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj
SpeedControl.elf: CMakeFiles/SpeedControl.dir/build.make
SpeedControl.elf: libuno_Servo.a
SpeedControl.elf: libuno_CORE.a
SpeedControl.elf: CMakeFiles/SpeedControl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SpeedControl.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SpeedControl.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating EEP image"
	/usr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.elf /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.eep
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating HEX image"
	/usr/bin/avr-objcopy -O ihex -R .eeprom /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.elf /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Calculating image size"
	/home/graham/clion/bin/cmake/bin/cmake -DFIRMWARE_IMAGE=/home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.elf -DMCU=atmega2560 -DEEPROM_IMAGE=/home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.eep -P /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

# Rule to build all files generated by this target.
CMakeFiles/SpeedControl.dir/build: SpeedControl.elf

.PHONY : CMakeFiles/SpeedControl.dir/build

CMakeFiles/SpeedControl.dir/requires: CMakeFiles/SpeedControl.dir/SpeedControl_test_harness.ino.cpp.obj.requires

.PHONY : CMakeFiles/SpeedControl.dir/requires

CMakeFiles/SpeedControl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpeedControl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpeedControl.dir/clean

CMakeFiles/SpeedControl.dir/depend: SpeedControl_test_harness.ino.cpp
	cd /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/projects/robot1/cpp/SpeedControl /home/graham/projects/robot1/cpp/SpeedControl /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug /home/graham/projects/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles/SpeedControl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpeedControl.dir/depend
