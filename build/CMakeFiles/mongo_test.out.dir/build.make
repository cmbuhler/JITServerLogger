# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cmbuhler/dev/JITServerLogger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cmbuhler/dev/JITServerLogger/build

# Include any dependencies generated for this target.
include CMakeFiles/mongo_test.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mongo_test.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mongo_test.out.dir/flags.make

CMakeFiles/mongo_test.out.dir/Test.cpp.o: CMakeFiles/mongo_test.out.dir/flags.make
CMakeFiles/mongo_test.out.dir/Test.cpp.o: ../Test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cmbuhler/dev/JITServerLogger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mongo_test.out.dir/Test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mongo_test.out.dir/Test.cpp.o -c /home/cmbuhler/dev/JITServerLogger/Test.cpp

CMakeFiles/mongo_test.out.dir/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mongo_test.out.dir/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cmbuhler/dev/JITServerLogger/Test.cpp > CMakeFiles/mongo_test.out.dir/Test.cpp.i

CMakeFiles/mongo_test.out.dir/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mongo_test.out.dir/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cmbuhler/dev/JITServerLogger/Test.cpp -o CMakeFiles/mongo_test.out.dir/Test.cpp.s

CMakeFiles/mongo_test.out.dir/Test.cpp.o.requires:

.PHONY : CMakeFiles/mongo_test.out.dir/Test.cpp.o.requires

CMakeFiles/mongo_test.out.dir/Test.cpp.o.provides: CMakeFiles/mongo_test.out.dir/Test.cpp.o.requires
	$(MAKE) -f CMakeFiles/mongo_test.out.dir/build.make CMakeFiles/mongo_test.out.dir/Test.cpp.o.provides.build
.PHONY : CMakeFiles/mongo_test.out.dir/Test.cpp.o.provides

CMakeFiles/mongo_test.out.dir/Test.cpp.o.provides.build: CMakeFiles/mongo_test.out.dir/Test.cpp.o


CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o: CMakeFiles/mongo_test.out.dir/flags.make
CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o: ../MongoLogger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cmbuhler/dev/JITServerLogger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o -c /home/cmbuhler/dev/JITServerLogger/MongoLogger.cpp

CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cmbuhler/dev/JITServerLogger/MongoLogger.cpp > CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.i

CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cmbuhler/dev/JITServerLogger/MongoLogger.cpp -o CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.s

CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.requires:

.PHONY : CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.requires

CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.provides: CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.requires
	$(MAKE) -f CMakeFiles/mongo_test.out.dir/build.make CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.provides.build
.PHONY : CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.provides

CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.provides.build: CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o


# Object files for target mongo_test.out
mongo_test_out_OBJECTS = \
"CMakeFiles/mongo_test.out.dir/Test.cpp.o" \
"CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o"

# External object files for target mongo_test.out
mongo_test_out_EXTERNAL_OBJECTS =

mongo_test.out: CMakeFiles/mongo_test.out.dir/Test.cpp.o
mongo_test.out: CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o
mongo_test.out: CMakeFiles/mongo_test.out.dir/build.make
mongo_test.out: /usr/local/lib/libmongocxx.so
mongo_test.out: /usr/local/lib/libbsoncxx.so
mongo_test.out: /usr/local/lib/libbsoncxx.so
mongo_test.out: CMakeFiles/mongo_test.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cmbuhler/dev/JITServerLogger/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable mongo_test.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mongo_test.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mongo_test.out.dir/build: mongo_test.out

.PHONY : CMakeFiles/mongo_test.out.dir/build

CMakeFiles/mongo_test.out.dir/requires: CMakeFiles/mongo_test.out.dir/Test.cpp.o.requires
CMakeFiles/mongo_test.out.dir/requires: CMakeFiles/mongo_test.out.dir/MongoLogger.cpp.o.requires

.PHONY : CMakeFiles/mongo_test.out.dir/requires

CMakeFiles/mongo_test.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mongo_test.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mongo_test.out.dir/clean

CMakeFiles/mongo_test.out.dir/depend:
	cd /home/cmbuhler/dev/JITServerLogger/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cmbuhler/dev/JITServerLogger /home/cmbuhler/dev/JITServerLogger /home/cmbuhler/dev/JITServerLogger/build /home/cmbuhler/dev/JITServerLogger/build /home/cmbuhler/dev/JITServerLogger/build/CMakeFiles/mongo_test.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mongo_test.out.dir/depend

