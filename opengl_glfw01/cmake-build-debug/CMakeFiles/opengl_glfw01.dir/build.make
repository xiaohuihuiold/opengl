# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/xhh/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5153.40/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/xhh/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.5153.40/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xhh/CLionProjects/opengl/opengl_glfw01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/opengl_glfw01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opengl_glfw01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opengl_glfw01.dir/flags.make

CMakeFiles/opengl_glfw01.dir/src/main.cpp.o: CMakeFiles/opengl_glfw01.dir/flags.make
CMakeFiles/opengl_glfw01.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opengl_glfw01.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_glfw01.dir/src/main.cpp.o -c /home/xhh/CLionProjects/opengl/opengl_glfw01/src/main.cpp

CMakeFiles/opengl_glfw01.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_glfw01.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xhh/CLionProjects/opengl/opengl_glfw01/src/main.cpp > CMakeFiles/opengl_glfw01.dir/src/main.cpp.i

CMakeFiles/opengl_glfw01.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_glfw01.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xhh/CLionProjects/opengl/opengl_glfw01/src/main.cpp -o CMakeFiles/opengl_glfw01.dir/src/main.cpp.s

CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.o: CMakeFiles/opengl_glfw01.dir/flags.make
CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.o: ../src/shader/Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.o -c /home/xhh/CLionProjects/opengl/opengl_glfw01/src/shader/Shader.cpp

CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xhh/CLionProjects/opengl/opengl_glfw01/src/shader/Shader.cpp > CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.i

CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xhh/CLionProjects/opengl/opengl_glfw01/src/shader/Shader.cpp -o CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.s

CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.o: CMakeFiles/opengl_glfw01.dir/flags.make
CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.o: ../src/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.o -c /home/xhh/CLionProjects/opengl/opengl_glfw01/src/stb_image.cpp

CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xhh/CLionProjects/opengl/opengl_glfw01/src/stb_image.cpp > CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.i

CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xhh/CLionProjects/opengl/opengl_glfw01/src/stb_image.cpp -o CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.s

# Object files for target opengl_glfw01
opengl_glfw01_OBJECTS = \
"CMakeFiles/opengl_glfw01.dir/src/main.cpp.o" \
"CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.o" \
"CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.o"

# External object files for target opengl_glfw01
opengl_glfw01_EXTERNAL_OBJECTS =

opengl_glfw01: CMakeFiles/opengl_glfw01.dir/src/main.cpp.o
opengl_glfw01: CMakeFiles/opengl_glfw01.dir/src/shader/Shader.cpp.o
opengl_glfw01: CMakeFiles/opengl_glfw01.dir/src/stb_image.cpp.o
opengl_glfw01: CMakeFiles/opengl_glfw01.dir/build.make
opengl_glfw01: libglad.a
opengl_glfw01: CMakeFiles/opengl_glfw01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable opengl_glfw01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opengl_glfw01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opengl_glfw01.dir/build: opengl_glfw01

.PHONY : CMakeFiles/opengl_glfw01.dir/build

CMakeFiles/opengl_glfw01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opengl_glfw01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opengl_glfw01.dir/clean

CMakeFiles/opengl_glfw01.dir/depend:
	cd /home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xhh/CLionProjects/opengl/opengl_glfw01 /home/xhh/CLionProjects/opengl/opengl_glfw01 /home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug /home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug /home/xhh/CLionProjects/opengl/opengl_glfw01/cmake-build-debug/CMakeFiles/opengl_glfw01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opengl_glfw01.dir/depend

