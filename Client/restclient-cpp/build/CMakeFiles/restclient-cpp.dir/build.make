# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/restclient-cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/restclient-cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/restclient-cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/restclient-cpp.dir/flags.make

CMakeFiles/restclient-cpp.dir/source/restclient.cc.o: CMakeFiles/restclient-cpp.dir/flags.make
CMakeFiles/restclient-cpp.dir/source/restclient.cc.o: /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/restclient.cc
CMakeFiles/restclient-cpp.dir/source/restclient.cc.o: CMakeFiles/restclient-cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/restclient-cpp.dir/source/restclient.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/restclient-cpp.dir/source/restclient.cc.o -MF CMakeFiles/restclient-cpp.dir/source/restclient.cc.o.d -o CMakeFiles/restclient-cpp.dir/source/restclient.cc.o -c /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/restclient.cc

CMakeFiles/restclient-cpp.dir/source/restclient.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/restclient-cpp.dir/source/restclient.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/restclient.cc > CMakeFiles/restclient-cpp.dir/source/restclient.cc.i

CMakeFiles/restclient-cpp.dir/source/restclient.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/restclient-cpp.dir/source/restclient.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/restclient.cc -o CMakeFiles/restclient-cpp.dir/source/restclient.cc.s

CMakeFiles/restclient-cpp.dir/source/connection.cc.o: CMakeFiles/restclient-cpp.dir/flags.make
CMakeFiles/restclient-cpp.dir/source/connection.cc.o: /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/connection.cc
CMakeFiles/restclient-cpp.dir/source/connection.cc.o: CMakeFiles/restclient-cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/restclient-cpp.dir/source/connection.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/restclient-cpp.dir/source/connection.cc.o -MF CMakeFiles/restclient-cpp.dir/source/connection.cc.o.d -o CMakeFiles/restclient-cpp.dir/source/connection.cc.o -c /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/connection.cc

CMakeFiles/restclient-cpp.dir/source/connection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/restclient-cpp.dir/source/connection.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/connection.cc > CMakeFiles/restclient-cpp.dir/source/connection.cc.i

CMakeFiles/restclient-cpp.dir/source/connection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/restclient-cpp.dir/source/connection.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/connection.cc -o CMakeFiles/restclient-cpp.dir/source/connection.cc.s

CMakeFiles/restclient-cpp.dir/source/helpers.cc.o: CMakeFiles/restclient-cpp.dir/flags.make
CMakeFiles/restclient-cpp.dir/source/helpers.cc.o: /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/helpers.cc
CMakeFiles/restclient-cpp.dir/source/helpers.cc.o: CMakeFiles/restclient-cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/restclient-cpp.dir/source/helpers.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/restclient-cpp.dir/source/helpers.cc.o -MF CMakeFiles/restclient-cpp.dir/source/helpers.cc.o.d -o CMakeFiles/restclient-cpp.dir/source/helpers.cc.o -c /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/helpers.cc

CMakeFiles/restclient-cpp.dir/source/helpers.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/restclient-cpp.dir/source/helpers.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/helpers.cc > CMakeFiles/restclient-cpp.dir/source/helpers.cc.i

CMakeFiles/restclient-cpp.dir/source/helpers.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/restclient-cpp.dir/source/helpers.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/source/helpers.cc -o CMakeFiles/restclient-cpp.dir/source/helpers.cc.s

# Object files for target restclient-cpp
restclient__cpp_OBJECTS = \
"CMakeFiles/restclient-cpp.dir/source/restclient.cc.o" \
"CMakeFiles/restclient-cpp.dir/source/connection.cc.o" \
"CMakeFiles/restclient-cpp.dir/source/helpers.cc.o"

# External object files for target restclient-cpp
restclient__cpp_EXTERNAL_OBJECTS =

librestclient-cpp.2.1.1.dylib: CMakeFiles/restclient-cpp.dir/source/restclient.cc.o
librestclient-cpp.2.1.1.dylib: CMakeFiles/restclient-cpp.dir/source/connection.cc.o
librestclient-cpp.2.1.1.dylib: CMakeFiles/restclient-cpp.dir/source/helpers.cc.o
librestclient-cpp.2.1.1.dylib: CMakeFiles/restclient-cpp.dir/build.make
librestclient-cpp.2.1.1.dylib: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/usr/lib/libcurl.tbd
librestclient-cpp.2.1.1.dylib: CMakeFiles/restclient-cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library librestclient-cpp.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/restclient-cpp.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library librestclient-cpp.2.1.1.dylib librestclient-cpp.2.1.1.dylib librestclient-cpp.dylib

librestclient-cpp.dylib: librestclient-cpp.2.1.1.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate librestclient-cpp.dylib

# Rule to build all files generated by this target.
CMakeFiles/restclient-cpp.dir/build: librestclient-cpp.dylib
.PHONY : CMakeFiles/restclient-cpp.dir/build

CMakeFiles/restclient-cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/restclient-cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/restclient-cpp.dir/clean

CMakeFiles/restclient-cpp.dir/depend:
	cd /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build /Users/rumighosh/github/TeamProject/CVNPlusOne/Client/restclient-cpp/build/CMakeFiles/restclient-cpp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/restclient-cpp.dir/depend

