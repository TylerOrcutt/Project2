# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/twittumz/Project2/Project2/Project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/twittumz/Project2/Project2/Project2

# Include any dependencies generated for this target.
include CMakeFiles/kal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kal.dir/flags.make

CMakeFiles/kal.dir/main.cpp.o: CMakeFiles/kal.dir/flags.make
CMakeFiles/kal.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/twittumz/Project2/Project2/Project2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/kal.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kal.dir/main.cpp.o -c /home/twittumz/Project2/Project2/Project2/main.cpp

CMakeFiles/kal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kal.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/twittumz/Project2/Project2/Project2/main.cpp > CMakeFiles/kal.dir/main.cpp.i

CMakeFiles/kal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kal.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/twittumz/Project2/Project2/Project2/main.cpp -o CMakeFiles/kal.dir/main.cpp.s

CMakeFiles/kal.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/kal.dir/main.cpp.o.requires

CMakeFiles/kal.dir/main.cpp.o.provides: CMakeFiles/kal.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/kal.dir/build.make CMakeFiles/kal.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/kal.dir/main.cpp.o.provides

CMakeFiles/kal.dir/main.cpp.o.provides.build: CMakeFiles/kal.dir/main.cpp.o

# Object files for target kal
kal_OBJECTS = \
"CMakeFiles/kal.dir/main.cpp.o"

# External object files for target kal
kal_EXTERNAL_OBJECTS =

kal: CMakeFiles/kal.dir/main.cpp.o
kal: CMakeFiles/kal.dir/build.make
kal: /usr/lib/x86_64-linux-gnu/libpango-1.0.so
kal: /usr/lib/x86_64-linux-gnu/libglib-2.0.so
kal: /usr/lib/libSOIL.so
kal: /usr/lib/x86_64-linux-gnu/libpango-1.0.so
kal: /usr/lib/x86_64-linux-gnu/libglib-2.0.so
kal: /usr/lib/libSOIL.so
kal: CMakeFiles/kal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable kal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kal.dir/build: kal
.PHONY : CMakeFiles/kal.dir/build

CMakeFiles/kal.dir/requires: CMakeFiles/kal.dir/main.cpp.o.requires
.PHONY : CMakeFiles/kal.dir/requires

CMakeFiles/kal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kal.dir/clean

CMakeFiles/kal.dir/depend:
	cd /home/twittumz/Project2/Project2/Project2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/twittumz/Project2/Project2/Project2 /home/twittumz/Project2/Project2/Project2 /home/twittumz/Project2/Project2/Project2 /home/twittumz/Project2/Project2/Project2 /home/twittumz/Project2/Project2/Project2/CMakeFiles/kal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kal.dir/depend

