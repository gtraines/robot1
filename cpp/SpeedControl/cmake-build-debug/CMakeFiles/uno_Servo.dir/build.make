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

# Include any dependencies generated for this target.
include CMakeFiles/uno_Servo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uno_Servo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uno_Servo.dir/flags.make

CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj: CMakeFiles/uno_Servo.dir/flags.make
CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj: /usr/share/arduino/libraries/Servo/Servo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj"
	/usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj -c /usr/share/arduino/libraries/Servo/Servo.cpp

CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/share/arduino/libraries/Servo/Servo.cpp > CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.i

CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/share/arduino/libraries/Servo/Servo.cpp -o CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.s

CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.requires:

.PHONY : CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.requires

CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.provides: CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.requires
	$(MAKE) -f CMakeFiles/uno_Servo.dir/build.make CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.provides.build
.PHONY : CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.provides

CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.provides.build: CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj


# Object files for target uno_Servo
uno_Servo_OBJECTS = \
"CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj"

# External object files for target uno_Servo
uno_Servo_EXTERNAL_OBJECTS =

libuno_Servo.a: CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj
libuno_Servo.a: CMakeFiles/uno_Servo.dir/build.make
libuno_Servo.a: CMakeFiles/uno_Servo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libuno_Servo.a"
	$(CMAKE_COMMAND) -P CMakeFiles/uno_Servo.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uno_Servo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uno_Servo.dir/build: libuno_Servo.a

.PHONY : CMakeFiles/uno_Servo.dir/build

CMakeFiles/uno_Servo.dir/requires: CMakeFiles/uno_Servo.dir/usr/share/arduino/libraries/Servo/Servo.cpp.obj.requires

.PHONY : CMakeFiles/uno_Servo.dir/requires

CMakeFiles/uno_Servo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uno_Servo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uno_Servo.dir/clean

CMakeFiles/uno_Servo.dir/depend:
	cd /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/_Source/robot1/cpp/SpeedControl /home/graham/_Source/robot1/cpp/SpeedControl /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug /home/graham/_Source/robot1/cpp/SpeedControl/cmake-build-debug/CMakeFiles/uno_Servo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uno_Servo.dir/depend

