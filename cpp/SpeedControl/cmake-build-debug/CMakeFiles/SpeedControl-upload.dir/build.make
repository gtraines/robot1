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
CMAKE_COMMAND = /home/graham/clion2017/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/graham/clion2017/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/graham/_Source/robot1/cpp/SpeedControl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug

# Utility rule file for SpeedControl-upload.

# Include the progress variables for this target.
include CMakeFiles/SpeedControl-upload.dir/progress.make

CMakeFiles/SpeedControl-upload: SpeedControl.elf
	/usr/share/arduino/hardware/tools/avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -patmega2560 -cwiring -b115200 -P/dev/ttyACM0 -D -V -Uflash:w:/home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.hex:i -Ueeprom:w:/home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug/SpeedControl.eep:i

SpeedControl-upload: CMakeFiles/SpeedControl-upload
SpeedControl-upload: CMakeFiles/SpeedControl-upload.dir/build.make

.PHONY : SpeedControl-upload

# Rule to build all files generated by this target.
CMakeFiles/SpeedControl-upload.dir/build: SpeedControl-upload

.PHONY : CMakeFiles/SpeedControl-upload.dir/build

CMakeFiles/SpeedControl-upload.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpeedControl-upload.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpeedControl-upload.dir/clean

CMakeFiles/SpeedControl-upload.dir/depend:
	cd /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/_Source/robot1/cpp/SpeedControl /home/graham/_Source/robot1/cpp/SpeedControl /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles/SpeedControl-upload.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpeedControl-upload.dir/depend

