# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\fl156\Desktop\Practica2MH

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\fl156\Desktop\Practica2MH\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AM-10-0.1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AM-10-0.1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AM-10-0.1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AM-10-0.1.dir/flags.make

CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj: CMakeFiles/AM-10-0.1.dir/flags.make
CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj: CMakeFiles/AM-10-0.1.dir/includes_CXX.rsp
CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj: ../src/AM-10-0.1.cpp
CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj: CMakeFiles/AM-10-0.1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\fl156\Desktop\Practica2MH\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj -MF CMakeFiles\AM-10-0.1.dir\src\AM-10-0.1.cpp.obj.d -o CMakeFiles\AM-10-0.1.dir\src\AM-10-0.1.cpp.obj -c C:\Users\fl156\Desktop\Practica2MH\src\AM-10-0.1.cpp

CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\fl156\Desktop\Practica2MH\src\AM-10-0.1.cpp > CMakeFiles\AM-10-0.1.dir\src\AM-10-0.1.cpp.i

CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\fl156\Desktop\Practica2MH\src\AM-10-0.1.cpp -o CMakeFiles\AM-10-0.1.dir\src\AM-10-0.1.cpp.s

# Object files for target AM-10-0.1
AM__10__0_1_OBJECTS = \
"CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj"

# External object files for target AM-10-0.1
AM__10__0_1_EXTERNAL_OBJECTS =

AM-10-0.1.exe: CMakeFiles/AM-10-0.1.dir/src/AM-10-0.1.cpp.obj
AM-10-0.1.exe: CMakeFiles/AM-10-0.1.dir/build.make
AM-10-0.1.exe: libProblem.a
AM-10-0.1.exe: libSolution_enteros.a
AM-10-0.1.exe: libbl.a
AM-10-0.1.exe: CMakeFiles/AM-10-0.1.dir/linklibs.rsp
AM-10-0.1.exe: CMakeFiles/AM-10-0.1.dir/objects1.rsp
AM-10-0.1.exe: CMakeFiles/AM-10-0.1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\fl156\Desktop\Practica2MH\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AM-10-0.1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AM-10-0.1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AM-10-0.1.dir/build: AM-10-0.1.exe
.PHONY : CMakeFiles/AM-10-0.1.dir/build

CMakeFiles/AM-10-0.1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\AM-10-0.1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/AM-10-0.1.dir/clean

CMakeFiles/AM-10-0.1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\fl156\Desktop\Practica2MH C:\Users\fl156\Desktop\Practica2MH C:\Users\fl156\Desktop\Practica2MH\cmake-build-debug C:\Users\fl156\Desktop\Practica2MH\cmake-build-debug C:\Users\fl156\Desktop\Practica2MH\cmake-build-debug\CMakeFiles\AM-10-0.1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AM-10-0.1.dir/depend

