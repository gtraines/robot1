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
CMAKE_SOURCE_DIR = /home/graham/Source/robot1/sketches

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/graham/Source/robot1/sketches/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mega_list.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mega_list.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mega_list.dir/flags.make

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj: ../libraries/Arduino_FreeRTOS/variantHooks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj"
	/usr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/variantHooks.cpp

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.i"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/variantHooks.cpp > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.s"
	/usr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/variantHooks.cpp -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj: ../libraries/Arduino_FreeRTOS/croutine.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/croutine.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/croutine.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/croutine.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj: ../libraries/Arduino_FreeRTOS/event_groups.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/event_groups.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/event_groups.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/event_groups.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj: ../libraries/Arduino_FreeRTOS/heap_3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/heap_3.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/heap_3.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/heap_3.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj: ../libraries/Arduino_FreeRTOS/list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/list.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/list.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/list.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj: ../libraries/Arduino_FreeRTOS/port.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/port.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/port.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/port.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj: ../libraries/Arduino_FreeRTOS/queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/queue.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/queue.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/queue.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj: ../libraries/Arduino_FreeRTOS/stream_buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/stream_buffer.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/stream_buffer.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/stream_buffer.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj: ../libraries/Arduino_FreeRTOS/tasks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/tasks.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/tasks.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/tasks.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj


CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj: CMakeFiles/mega_list.dir/flags.make
CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj: ../libraries/Arduino_FreeRTOS/timers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj   -c /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/timers.c

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.i"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/timers.c > CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.i

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.s"
	/usr/bin/avr-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/graham/Source/robot1/sketches/libraries/Arduino_FreeRTOS/timers.c -o CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.s

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.requires:

.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.requires

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.provides: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.requires
	$(MAKE) -f CMakeFiles/mega_list.dir/build.make CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.provides.build
.PHONY : CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.provides

CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.provides.build: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj


# Object files for target mega_list
mega_list_OBJECTS = \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj" \
"CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj"

# External object files for target mega_list
mega_list_EXTERNAL_OBJECTS =

libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj
libmega_list.a: CMakeFiles/mega_list.dir/build.make
libmega_list.a: CMakeFiles/mega_list.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library libmega_list.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mega_list.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mega_list.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mega_list.dir/build: libmega_list.a

.PHONY : CMakeFiles/mega_list.dir/build

CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/variantHooks.cpp.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/croutine.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/event_groups.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/heap_3.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/list.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/port.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/queue.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/stream_buffer.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/tasks.c.obj.requires
CMakeFiles/mega_list.dir/requires: CMakeFiles/mega_list.dir/libraries/Arduino_FreeRTOS/timers.c.obj.requires

.PHONY : CMakeFiles/mega_list.dir/requires

CMakeFiles/mega_list.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mega_list.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mega_list.dir/clean

CMakeFiles/mega_list.dir/depend:
	cd /home/graham/Source/robot1/sketches/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/graham/Source/robot1/sketches /home/graham/Source/robot1/sketches /home/graham/Source/robot1/sketches/cmake-build-debug /home/graham/Source/robot1/sketches/cmake-build-debug /home/graham/Source/robot1/sketches/cmake-build-debug/CMakeFiles/mega_list.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mega_list.dir/depend

