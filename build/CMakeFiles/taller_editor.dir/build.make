# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build

# Include any dependencies generated for this target.
include CMakeFiles/taller_editor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/taller_editor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/taller_editor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/taller_editor.dir/flags.make

CMakeFiles/taller_editor.dir/editor/main.cpp.o: CMakeFiles/taller_editor.dir/flags.make
CMakeFiles/taller_editor.dir/editor/main.cpp.o: ../editor/main.cpp
CMakeFiles/taller_editor.dir/editor/main.cpp.o: CMakeFiles/taller_editor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/taller_editor.dir/editor/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_editor.dir/editor/main.cpp.o -MF CMakeFiles/taller_editor.dir/editor/main.cpp.o.d -o CMakeFiles/taller_editor.dir/editor/main.cpp.o -c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/editor/main.cpp

CMakeFiles/taller_editor.dir/editor/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_editor.dir/editor/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/editor/main.cpp > CMakeFiles/taller_editor.dir/editor/main.cpp.i

CMakeFiles/taller_editor.dir/editor/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_editor.dir/editor/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/editor/main.cpp -o CMakeFiles/taller_editor.dir/editor/main.cpp.s

# Object files for target taller_editor
taller_editor_OBJECTS = \
"CMakeFiles/taller_editor.dir/editor/main.cpp.o"

# External object files for target taller_editor
taller_editor_EXTERNAL_OBJECTS =

taller_editor: CMakeFiles/taller_editor.dir/editor/main.cpp.o
taller_editor: CMakeFiles/taller_editor.dir/build.make
taller_editor: libtaller_common.a
taller_editor: _deps/libsdl2pp-build/libSDL2pp.so.8.3.0
taller_editor: /usr/lib/x86_64-linux-gnu/libSDL2main.a
taller_editor: /usr/local/lib/libSDL2_image-2.0.so.0.600.3
taller_editor: /usr/local/lib/libSDL2_ttf-2.0.so.0.2000.2
taller_editor: /usr/local/lib/libSDL2_mixer-2.0.so.0.600.3
taller_editor: /usr/lib/x86_64-linux-gnu/libSDL2.so
taller_editor: CMakeFiles/taller_editor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable taller_editor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/taller_editor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/taller_editor.dir/build: taller_editor
.PHONY : CMakeFiles/taller_editor.dir/build

CMakeFiles/taller_editor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/taller_editor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/taller_editor.dir/clean

CMakeFiles/taller_editor.dir/depend:
	cd /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles/taller_editor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/taller_editor.dir/depend

