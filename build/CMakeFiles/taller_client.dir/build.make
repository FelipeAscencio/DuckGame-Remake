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
CMAKE_SOURCE_DIR = /home/axelon/Documents/Taller/DuckGame-g2-20242c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/axelon/Documents/Taller/DuckGame-g2-20242c/build

# Include any dependencies generated for this target.
include CMakeFiles/taller_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/taller_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/taller_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/taller_client.dir/flags.make

CMakeFiles/taller_client.dir/client/main.cpp.o: CMakeFiles/taller_client.dir/flags.make
CMakeFiles/taller_client.dir/client/main.cpp.o: ../client/main.cpp
CMakeFiles/taller_client.dir/client/main.cpp.o: CMakeFiles/taller_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/taller_client.dir/client/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_client.dir/client/main.cpp.o -MF CMakeFiles/taller_client.dir/client/main.cpp.o.d -o CMakeFiles/taller_client.dir/client/main.cpp.o -c /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/main.cpp

CMakeFiles/taller_client.dir/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_client.dir/client/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/main.cpp > CMakeFiles/taller_client.dir/client/main.cpp.i

CMakeFiles/taller_client.dir/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_client.dir/client/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/main.cpp -o CMakeFiles/taller_client.dir/client/main.cpp.s

CMakeFiles/taller_client.dir/client/client_handler.cpp.o: CMakeFiles/taller_client.dir/flags.make
CMakeFiles/taller_client.dir/client/client_handler.cpp.o: ../client/client_handler.cpp
CMakeFiles/taller_client.dir/client/client_handler.cpp.o: CMakeFiles/taller_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/taller_client.dir/client/client_handler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_client.dir/client/client_handler.cpp.o -MF CMakeFiles/taller_client.dir/client/client_handler.cpp.o.d -o CMakeFiles/taller_client.dir/client/client_handler.cpp.o -c /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_handler.cpp

CMakeFiles/taller_client.dir/client/client_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_client.dir/client/client_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_handler.cpp > CMakeFiles/taller_client.dir/client/client_handler.cpp.i

CMakeFiles/taller_client.dir/client/client_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_client.dir/client/client_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_handler.cpp -o CMakeFiles/taller_client.dir/client/client_handler.cpp.s

CMakeFiles/taller_client.dir/client/client_controlador.cpp.o: CMakeFiles/taller_client.dir/flags.make
CMakeFiles/taller_client.dir/client/client_controlador.cpp.o: ../client/client_controlador.cpp
CMakeFiles/taller_client.dir/client/client_controlador.cpp.o: CMakeFiles/taller_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/taller_client.dir/client/client_controlador.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_client.dir/client/client_controlador.cpp.o -MF CMakeFiles/taller_client.dir/client/client_controlador.cpp.o.d -o CMakeFiles/taller_client.dir/client/client_controlador.cpp.o -c /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_controlador.cpp

CMakeFiles/taller_client.dir/client/client_controlador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_client.dir/client/client_controlador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_controlador.cpp > CMakeFiles/taller_client.dir/client/client_controlador.cpp.i

CMakeFiles/taller_client.dir/client/client_controlador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_client.dir/client/client_controlador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_controlador.cpp -o CMakeFiles/taller_client.dir/client/client_controlador.cpp.s

CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o: CMakeFiles/taller_client.dir/flags.make
CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o: ../client/client_dibujador.cpp
CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o: CMakeFiles/taller_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o -MF CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o.d -o CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o -c /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_dibujador.cpp

CMakeFiles/taller_client.dir/client/client_dibujador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_client.dir/client/client_dibujador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_dibujador.cpp > CMakeFiles/taller_client.dir/client/client_dibujador.cpp.i

CMakeFiles/taller_client.dir/client/client_dibujador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_client.dir/client/client_dibujador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_dibujador.cpp -o CMakeFiles/taller_client.dir/client/client_dibujador.cpp.s

CMakeFiles/taller_client.dir/client/client_parseador.cpp.o: CMakeFiles/taller_client.dir/flags.make
CMakeFiles/taller_client.dir/client/client_parseador.cpp.o: ../client/client_parseador.cpp
CMakeFiles/taller_client.dir/client/client_parseador.cpp.o: CMakeFiles/taller_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/taller_client.dir/client/client_parseador.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/taller_client.dir/client/client_parseador.cpp.o -MF CMakeFiles/taller_client.dir/client/client_parseador.cpp.o.d -o CMakeFiles/taller_client.dir/client/client_parseador.cpp.o -c /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_parseador.cpp

CMakeFiles/taller_client.dir/client/client_parseador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller_client.dir/client/client_parseador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_parseador.cpp > CMakeFiles/taller_client.dir/client/client_parseador.cpp.i

CMakeFiles/taller_client.dir/client/client_parseador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller_client.dir/client/client_parseador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/axelon/Documents/Taller/DuckGame-g2-20242c/client/client_parseador.cpp -o CMakeFiles/taller_client.dir/client/client_parseador.cpp.s

# Object files for target taller_client
taller_client_OBJECTS = \
"CMakeFiles/taller_client.dir/client/main.cpp.o" \
"CMakeFiles/taller_client.dir/client/client_handler.cpp.o" \
"CMakeFiles/taller_client.dir/client/client_controlador.cpp.o" \
"CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o" \
"CMakeFiles/taller_client.dir/client/client_parseador.cpp.o"

# External object files for target taller_client
taller_client_EXTERNAL_OBJECTS =

taller_client: CMakeFiles/taller_client.dir/client/main.cpp.o
taller_client: CMakeFiles/taller_client.dir/client/client_handler.cpp.o
taller_client: CMakeFiles/taller_client.dir/client/client_controlador.cpp.o
taller_client: CMakeFiles/taller_client.dir/client/client_dibujador.cpp.o
taller_client: CMakeFiles/taller_client.dir/client/client_parseador.cpp.o
taller_client: CMakeFiles/taller_client.dir/build.make
taller_client: libtaller_common.a
taller_client: _deps/libsdl2pp-build/libSDL2pp.so.8.3.0
taller_client: /usr/lib/x86_64-linux-gnu/libSDL2main.a
taller_client: /usr/local/lib/libSDL2_image-2.0.so.0.600.3
taller_client: /usr/local/lib/libSDL2_ttf-2.0.so.0.2000.2
taller_client: /usr/local/lib/libSDL2_mixer-2.0.so.0.600.3
taller_client: /usr/lib/x86_64-linux-gnu/libSDL2.so
taller_client: CMakeFiles/taller_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable taller_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/taller_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/taller_client.dir/build: taller_client
.PHONY : CMakeFiles/taller_client.dir/build

CMakeFiles/taller_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/taller_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/taller_client.dir/clean

CMakeFiles/taller_client.dir/depend:
	cd /home/axelon/Documents/Taller/DuckGame-g2-20242c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/axelon/Documents/Taller/DuckGame-g2-20242c /home/axelon/Documents/Taller/DuckGame-g2-20242c /home/axelon/Documents/Taller/DuckGame-g2-20242c/build /home/axelon/Documents/Taller/DuckGame-g2-20242c/build /home/axelon/Documents/Taller/DuckGame-g2-20242c/build/CMakeFiles/taller_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/taller_client.dir/depend

