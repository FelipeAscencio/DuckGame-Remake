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
include CMakeFiles/taller_common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/taller_common.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/taller_common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/taller_common.dir/flags.make

CMakeFiles/taller_common.dir/common/foo.cpp.o: CMakeFiles/taller_common.dir/flags.make
CMakeFiles/taller_common.dir/common/foo.cpp.o: ../common/foo.cpp
CMakeFiles/taller_common.dir/common/foo.cpp.o: CMakeFiles/taller_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/taller_common.dir/common/foo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_common.dir/common/foo.cpp.o -MF CMakeFiles/taller_common.dir/common/foo.cpp.o.d -o CMakeFiles/taller_common.dir/common/foo.cpp.o -c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/foo.cpp

CMakeFiles/taller_common.dir/common/foo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_common.dir/common/foo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/foo.cpp > CMakeFiles/taller_common.dir/common/foo.cpp.i

CMakeFiles/taller_common.dir/common/foo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_common.dir/common/foo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/foo.cpp -o CMakeFiles/taller_common.dir/common/foo.cpp.s

CMakeFiles/taller_common.dir/common/liberror.cpp.o: CMakeFiles/taller_common.dir/flags.make
CMakeFiles/taller_common.dir/common/liberror.cpp.o: ../common/liberror.cpp
CMakeFiles/taller_common.dir/common/liberror.cpp.o: CMakeFiles/taller_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/taller_common.dir/common/liberror.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_common.dir/common/liberror.cpp.o -MF CMakeFiles/taller_common.dir/common/liberror.cpp.o.d -o CMakeFiles/taller_common.dir/common/liberror.cpp.o -c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/liberror.cpp

CMakeFiles/taller_common.dir/common/liberror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_common.dir/common/liberror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/liberror.cpp > CMakeFiles/taller_common.dir/common/liberror.cpp.i

CMakeFiles/taller_common.dir/common/liberror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_common.dir/common/liberror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/liberror.cpp -o CMakeFiles/taller_common.dir/common/liberror.cpp.s

CMakeFiles/taller_common.dir/common/resolver.cpp.o: CMakeFiles/taller_common.dir/flags.make
CMakeFiles/taller_common.dir/common/resolver.cpp.o: ../common/resolver.cpp
CMakeFiles/taller_common.dir/common/resolver.cpp.o: CMakeFiles/taller_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/taller_common.dir/common/resolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_common.dir/common/resolver.cpp.o -MF CMakeFiles/taller_common.dir/common/resolver.cpp.o.d -o CMakeFiles/taller_common.dir/common/resolver.cpp.o -c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/resolver.cpp

CMakeFiles/taller_common.dir/common/resolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_common.dir/common/resolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/resolver.cpp > CMakeFiles/taller_common.dir/common/resolver.cpp.i

CMakeFiles/taller_common.dir/common/resolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_common.dir/common/resolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/resolver.cpp -o CMakeFiles/taller_common.dir/common/resolver.cpp.s

CMakeFiles/taller_common.dir/common/resolvererror.cpp.o: CMakeFiles/taller_common.dir/flags.make
CMakeFiles/taller_common.dir/common/resolvererror.cpp.o: ../common/resolvererror.cpp
CMakeFiles/taller_common.dir/common/resolvererror.cpp.o: CMakeFiles/taller_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/taller_common.dir/common/resolvererror.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_common.dir/common/resolvererror.cpp.o -MF CMakeFiles/taller_common.dir/common/resolvererror.cpp.o.d -o CMakeFiles/taller_common.dir/common/resolvererror.cpp.o -c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/resolvererror.cpp

CMakeFiles/taller_common.dir/common/resolvererror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_common.dir/common/resolvererror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/resolvererror.cpp > CMakeFiles/taller_common.dir/common/resolvererror.cpp.i

CMakeFiles/taller_common.dir/common/resolvererror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_common.dir/common/resolvererror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/resolvererror.cpp -o CMakeFiles/taller_common.dir/common/resolvererror.cpp.s

CMakeFiles/taller_common.dir/common/socket.cpp.o: CMakeFiles/taller_common.dir/flags.make
CMakeFiles/taller_common.dir/common/socket.cpp.o: ../common/socket.cpp
CMakeFiles/taller_common.dir/common/socket.cpp.o: CMakeFiles/taller_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/taller_common.dir/common/socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_common.dir/common/socket.cpp.o -MF CMakeFiles/taller_common.dir/common/socket.cpp.o.d -o CMakeFiles/taller_common.dir/common/socket.cpp.o -c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/socket.cpp

CMakeFiles/taller_common.dir/common/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_common.dir/common/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/socket.cpp > CMakeFiles/taller_common.dir/common/socket.cpp.i

CMakeFiles/taller_common.dir/common/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_common.dir/common/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/common/socket.cpp -o CMakeFiles/taller_common.dir/common/socket.cpp.s

# Object files for target taller_common
taller_common_OBJECTS = \
"CMakeFiles/taller_common.dir/common/foo.cpp.o" \
"CMakeFiles/taller_common.dir/common/liberror.cpp.o" \
"CMakeFiles/taller_common.dir/common/resolver.cpp.o" \
"CMakeFiles/taller_common.dir/common/resolvererror.cpp.o" \
"CMakeFiles/taller_common.dir/common/socket.cpp.o"

# External object files for target taller_common
taller_common_EXTERNAL_OBJECTS =

libtaller_common.a: CMakeFiles/taller_common.dir/common/foo.cpp.o
libtaller_common.a: CMakeFiles/taller_common.dir/common/liberror.cpp.o
libtaller_common.a: CMakeFiles/taller_common.dir/common/resolver.cpp.o
libtaller_common.a: CMakeFiles/taller_common.dir/common/resolvererror.cpp.o
libtaller_common.a: CMakeFiles/taller_common.dir/common/socket.cpp.o
libtaller_common.a: CMakeFiles/taller_common.dir/build.make
libtaller_common.a: CMakeFiles/taller_common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libtaller_common.a"
	$(CMAKE_COMMAND) -P CMakeFiles/taller_common.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/taller_common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/taller_common.dir/build: libtaller_common.a
.PHONY : CMakeFiles/taller_common.dir/build

CMakeFiles/taller_common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/taller_common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/taller_common.dir/clean

CMakeFiles/taller_common.dir/depend:
	cd /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build /mnt/c/Users/Usuario/Desktop/TPS/Duck-Game/DuckGame-g2-20242c/build/CMakeFiles/taller_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/taller_common.dir/depend

