# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build

# Include any dependencies generated for this target.
include CMakeFiles/handshake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/handshake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/handshake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/handshake.dir/flags.make

CMakeFiles/handshake.dir/main.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/main.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/main.cpp
CMakeFiles/handshake.dir/main.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/handshake.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/main.cpp.o -MF CMakeFiles/handshake.dir/main.cpp.o.d -o CMakeFiles/handshake.dir/main.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/main.cpp

CMakeFiles/handshake.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/main.cpp > CMakeFiles/handshake.dir/main.cpp.i

CMakeFiles/handshake.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/main.cpp -o CMakeFiles/handshake.dir/main.cpp.s

CMakeFiles/handshake.dir/peer_connect.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/peer_connect.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/peer_connect.cpp
CMakeFiles/handshake.dir/peer_connect.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/handshake.dir/peer_connect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/peer_connect.cpp.o -MF CMakeFiles/handshake.dir/peer_connect.cpp.o.d -o CMakeFiles/handshake.dir/peer_connect.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/peer_connect.cpp

CMakeFiles/handshake.dir/peer_connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/peer_connect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/peer_connect.cpp > CMakeFiles/handshake.dir/peer_connect.cpp.i

CMakeFiles/handshake.dir/peer_connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/peer_connect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/peer_connect.cpp -o CMakeFiles/handshake.dir/peer_connect.cpp.s

CMakeFiles/handshake.dir/tcp_connect.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/tcp_connect.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/tcp_connect.cpp
CMakeFiles/handshake.dir/tcp_connect.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/handshake.dir/tcp_connect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/tcp_connect.cpp.o -MF CMakeFiles/handshake.dir/tcp_connect.cpp.o.d -o CMakeFiles/handshake.dir/tcp_connect.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/tcp_connect.cpp

CMakeFiles/handshake.dir/tcp_connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/tcp_connect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/tcp_connect.cpp > CMakeFiles/handshake.dir/tcp_connect.cpp.i

CMakeFiles/handshake.dir/tcp_connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/tcp_connect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/tcp_connect.cpp -o CMakeFiles/handshake.dir/tcp_connect.cpp.s

CMakeFiles/handshake.dir/torrent_tracker.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/torrent_tracker.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_tracker.cpp
CMakeFiles/handshake.dir/torrent_tracker.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/handshake.dir/torrent_tracker.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/torrent_tracker.cpp.o -MF CMakeFiles/handshake.dir/torrent_tracker.cpp.o.d -o CMakeFiles/handshake.dir/torrent_tracker.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_tracker.cpp

CMakeFiles/handshake.dir/torrent_tracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/torrent_tracker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_tracker.cpp > CMakeFiles/handshake.dir/torrent_tracker.cpp.i

CMakeFiles/handshake.dir/torrent_tracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/torrent_tracker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_tracker.cpp -o CMakeFiles/handshake.dir/torrent_tracker.cpp.s

CMakeFiles/handshake.dir/torrent_file.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/torrent_file.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_file.cpp
CMakeFiles/handshake.dir/torrent_file.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/handshake.dir/torrent_file.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/torrent_file.cpp.o -MF CMakeFiles/handshake.dir/torrent_file.cpp.o.d -o CMakeFiles/handshake.dir/torrent_file.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_file.cpp

CMakeFiles/handshake.dir/torrent_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/torrent_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_file.cpp > CMakeFiles/handshake.dir/torrent_file.cpp.i

CMakeFiles/handshake.dir/torrent_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/torrent_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/torrent_file.cpp -o CMakeFiles/handshake.dir/torrent_file.cpp.s

CMakeFiles/handshake.dir/bencode.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/bencode.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/bencode.cpp
CMakeFiles/handshake.dir/bencode.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/handshake.dir/bencode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/bencode.cpp.o -MF CMakeFiles/handshake.dir/bencode.cpp.o.d -o CMakeFiles/handshake.dir/bencode.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/bencode.cpp

CMakeFiles/handshake.dir/bencode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/bencode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/bencode.cpp > CMakeFiles/handshake.dir/bencode.cpp.i

CMakeFiles/handshake.dir/bencode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/bencode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/bencode.cpp -o CMakeFiles/handshake.dir/bencode.cpp.s

CMakeFiles/handshake.dir/message.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/message.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/message.cpp
CMakeFiles/handshake.dir/message.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/handshake.dir/message.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/message.cpp.o -MF CMakeFiles/handshake.dir/message.cpp.o.d -o CMakeFiles/handshake.dir/message.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/message.cpp

CMakeFiles/handshake.dir/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/message.cpp > CMakeFiles/handshake.dir/message.cpp.i

CMakeFiles/handshake.dir/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/message.cpp -o CMakeFiles/handshake.dir/message.cpp.s

CMakeFiles/handshake.dir/byte_tools.cpp.o: CMakeFiles/handshake.dir/flags.make
CMakeFiles/handshake.dir/byte_tools.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/byte_tools.cpp
CMakeFiles/handshake.dir/byte_tools.cpp.o: CMakeFiles/handshake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/handshake.dir/byte_tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/handshake.dir/byte_tools.cpp.o -MF CMakeFiles/handshake.dir/byte_tools.cpp.o.d -o CMakeFiles/handshake.dir/byte_tools.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/byte_tools.cpp

CMakeFiles/handshake.dir/byte_tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/handshake.dir/byte_tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/byte_tools.cpp > CMakeFiles/handshake.dir/byte_tools.cpp.i

CMakeFiles/handshake.dir/byte_tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/handshake.dir/byte_tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/byte_tools.cpp -o CMakeFiles/handshake.dir/byte_tools.cpp.s

# Object files for target handshake
handshake_OBJECTS = \
"CMakeFiles/handshake.dir/main.cpp.o" \
"CMakeFiles/handshake.dir/peer_connect.cpp.o" \
"CMakeFiles/handshake.dir/tcp_connect.cpp.o" \
"CMakeFiles/handshake.dir/torrent_tracker.cpp.o" \
"CMakeFiles/handshake.dir/torrent_file.cpp.o" \
"CMakeFiles/handshake.dir/bencode.cpp.o" \
"CMakeFiles/handshake.dir/message.cpp.o" \
"CMakeFiles/handshake.dir/byte_tools.cpp.o"

# External object files for target handshake
handshake_EXTERNAL_OBJECTS =

handshake: CMakeFiles/handshake.dir/main.cpp.o
handshake: CMakeFiles/handshake.dir/peer_connect.cpp.o
handshake: CMakeFiles/handshake.dir/tcp_connect.cpp.o
handshake: CMakeFiles/handshake.dir/torrent_tracker.cpp.o
handshake: CMakeFiles/handshake.dir/torrent_file.cpp.o
handshake: CMakeFiles/handshake.dir/bencode.cpp.o
handshake: CMakeFiles/handshake.dir/message.cpp.o
handshake: CMakeFiles/handshake.dir/byte_tools.cpp.o
handshake: CMakeFiles/handshake.dir/build.make
handshake: /usr/lib/libssl.so
handshake: /usr/lib/libcrypto.so
handshake: _deps/cpr-build/cpr/libcpr.so.1.9.0
handshake: /usr/local/lib/libcurl.so.4.8.0
handshake: CMakeFiles/handshake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable handshake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/handshake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/handshake.dir/build: handshake
.PHONY : CMakeFiles/handshake.dir/build

CMakeFiles/handshake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/handshake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/handshake.dir/clean

CMakeFiles/handshake.dir/depend:
	cd /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build /home/marsel/mephi/programming-2/mmarss/project-part-4/handshake/cmake-build/CMakeFiles/handshake.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/handshake.dir/depend
