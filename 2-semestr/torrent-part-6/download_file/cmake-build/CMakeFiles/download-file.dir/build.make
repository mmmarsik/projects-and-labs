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
CMAKE_SOURCE_DIR = /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build

# Include any dependencies generated for this target.
include CMakeFiles/download-file.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/download-file.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/download-file.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/download-file.dir/flags.make

CMakeFiles/download-file.dir/main.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/main.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/main.cpp
CMakeFiles/download-file.dir/main.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/download-file.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/main.cpp.o -MF CMakeFiles/download-file.dir/main.cpp.o.d -o CMakeFiles/download-file.dir/main.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/main.cpp

CMakeFiles/download-file.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/main.cpp > CMakeFiles/download-file.dir/main.cpp.i

CMakeFiles/download-file.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/main.cpp -o CMakeFiles/download-file.dir/main.cpp.s

CMakeFiles/download-file.dir/peer_connect.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/peer_connect.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/peer_connect.cpp
CMakeFiles/download-file.dir/peer_connect.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/download-file.dir/peer_connect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/peer_connect.cpp.o -MF CMakeFiles/download-file.dir/peer_connect.cpp.o.d -o CMakeFiles/download-file.dir/peer_connect.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/peer_connect.cpp

CMakeFiles/download-file.dir/peer_connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/peer_connect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/peer_connect.cpp > CMakeFiles/download-file.dir/peer_connect.cpp.i

CMakeFiles/download-file.dir/peer_connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/peer_connect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/peer_connect.cpp -o CMakeFiles/download-file.dir/peer_connect.cpp.s

CMakeFiles/download-file.dir/tcp_connect.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/tcp_connect.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/tcp_connect.cpp
CMakeFiles/download-file.dir/tcp_connect.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/download-file.dir/tcp_connect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/tcp_connect.cpp.o -MF CMakeFiles/download-file.dir/tcp_connect.cpp.o.d -o CMakeFiles/download-file.dir/tcp_connect.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/tcp_connect.cpp

CMakeFiles/download-file.dir/tcp_connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/tcp_connect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/tcp_connect.cpp > CMakeFiles/download-file.dir/tcp_connect.cpp.i

CMakeFiles/download-file.dir/tcp_connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/tcp_connect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/tcp_connect.cpp -o CMakeFiles/download-file.dir/tcp_connect.cpp.s

CMakeFiles/download-file.dir/torrent_tracker.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/torrent_tracker.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_tracker.cpp
CMakeFiles/download-file.dir/torrent_tracker.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/download-file.dir/torrent_tracker.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/torrent_tracker.cpp.o -MF CMakeFiles/download-file.dir/torrent_tracker.cpp.o.d -o CMakeFiles/download-file.dir/torrent_tracker.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_tracker.cpp

CMakeFiles/download-file.dir/torrent_tracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/torrent_tracker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_tracker.cpp > CMakeFiles/download-file.dir/torrent_tracker.cpp.i

CMakeFiles/download-file.dir/torrent_tracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/torrent_tracker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_tracker.cpp -o CMakeFiles/download-file.dir/torrent_tracker.cpp.s

CMakeFiles/download-file.dir/torrent_file.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/torrent_file.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_file.cpp
CMakeFiles/download-file.dir/torrent_file.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/download-file.dir/torrent_file.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/torrent_file.cpp.o -MF CMakeFiles/download-file.dir/torrent_file.cpp.o.d -o CMakeFiles/download-file.dir/torrent_file.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_file.cpp

CMakeFiles/download-file.dir/torrent_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/torrent_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_file.cpp > CMakeFiles/download-file.dir/torrent_file.cpp.i

CMakeFiles/download-file.dir/torrent_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/torrent_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/torrent_file.cpp -o CMakeFiles/download-file.dir/torrent_file.cpp.s

CMakeFiles/download-file.dir/bencode.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/bencode.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/bencode.cpp
CMakeFiles/download-file.dir/bencode.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/download-file.dir/bencode.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/bencode.cpp.o -MF CMakeFiles/download-file.dir/bencode.cpp.o.d -o CMakeFiles/download-file.dir/bencode.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/bencode.cpp

CMakeFiles/download-file.dir/bencode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/bencode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/bencode.cpp > CMakeFiles/download-file.dir/bencode.cpp.i

CMakeFiles/download-file.dir/bencode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/bencode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/bencode.cpp -o CMakeFiles/download-file.dir/bencode.cpp.s

CMakeFiles/download-file.dir/message.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/message.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/message.cpp
CMakeFiles/download-file.dir/message.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/download-file.dir/message.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/message.cpp.o -MF CMakeFiles/download-file.dir/message.cpp.o.d -o CMakeFiles/download-file.dir/message.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/message.cpp

CMakeFiles/download-file.dir/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/message.cpp > CMakeFiles/download-file.dir/message.cpp.i

CMakeFiles/download-file.dir/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/message.cpp -o CMakeFiles/download-file.dir/message.cpp.s

CMakeFiles/download-file.dir/byte_tools.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/byte_tools.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/byte_tools.cpp
CMakeFiles/download-file.dir/byte_tools.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/download-file.dir/byte_tools.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/byte_tools.cpp.o -MF CMakeFiles/download-file.dir/byte_tools.cpp.o.d -o CMakeFiles/download-file.dir/byte_tools.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/byte_tools.cpp

CMakeFiles/download-file.dir/byte_tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/byte_tools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/byte_tools.cpp > CMakeFiles/download-file.dir/byte_tools.cpp.i

CMakeFiles/download-file.dir/byte_tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/byte_tools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/byte_tools.cpp -o CMakeFiles/download-file.dir/byte_tools.cpp.s

CMakeFiles/download-file.dir/piece_storage.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/piece_storage.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece_storage.cpp
CMakeFiles/download-file.dir/piece_storage.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/download-file.dir/piece_storage.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/piece_storage.cpp.o -MF CMakeFiles/download-file.dir/piece_storage.cpp.o.d -o CMakeFiles/download-file.dir/piece_storage.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece_storage.cpp

CMakeFiles/download-file.dir/piece_storage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/piece_storage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece_storage.cpp > CMakeFiles/download-file.dir/piece_storage.cpp.i

CMakeFiles/download-file.dir/piece_storage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/piece_storage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece_storage.cpp -o CMakeFiles/download-file.dir/piece_storage.cpp.s

CMakeFiles/download-file.dir/piece.cpp.o: CMakeFiles/download-file.dir/flags.make
CMakeFiles/download-file.dir/piece.cpp.o: /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece.cpp
CMakeFiles/download-file.dir/piece.cpp.o: CMakeFiles/download-file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/download-file.dir/piece.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/download-file.dir/piece.cpp.o -MF CMakeFiles/download-file.dir/piece.cpp.o.d -o CMakeFiles/download-file.dir/piece.cpp.o -c /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece.cpp

CMakeFiles/download-file.dir/piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/download-file.dir/piece.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece.cpp > CMakeFiles/download-file.dir/piece.cpp.i

CMakeFiles/download-file.dir/piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/download-file.dir/piece.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/piece.cpp -o CMakeFiles/download-file.dir/piece.cpp.s

# Object files for target download-file
download__file_OBJECTS = \
"CMakeFiles/download-file.dir/main.cpp.o" \
"CMakeFiles/download-file.dir/peer_connect.cpp.o" \
"CMakeFiles/download-file.dir/tcp_connect.cpp.o" \
"CMakeFiles/download-file.dir/torrent_tracker.cpp.o" \
"CMakeFiles/download-file.dir/torrent_file.cpp.o" \
"CMakeFiles/download-file.dir/bencode.cpp.o" \
"CMakeFiles/download-file.dir/message.cpp.o" \
"CMakeFiles/download-file.dir/byte_tools.cpp.o" \
"CMakeFiles/download-file.dir/piece_storage.cpp.o" \
"CMakeFiles/download-file.dir/piece.cpp.o"

# External object files for target download-file
download__file_EXTERNAL_OBJECTS =

download-file: CMakeFiles/download-file.dir/main.cpp.o
download-file: CMakeFiles/download-file.dir/peer_connect.cpp.o
download-file: CMakeFiles/download-file.dir/tcp_connect.cpp.o
download-file: CMakeFiles/download-file.dir/torrent_tracker.cpp.o
download-file: CMakeFiles/download-file.dir/torrent_file.cpp.o
download-file: CMakeFiles/download-file.dir/bencode.cpp.o
download-file: CMakeFiles/download-file.dir/message.cpp.o
download-file: CMakeFiles/download-file.dir/byte_tools.cpp.o
download-file: CMakeFiles/download-file.dir/piece_storage.cpp.o
download-file: CMakeFiles/download-file.dir/piece.cpp.o
download-file: CMakeFiles/download-file.dir/build.make
download-file: /usr/lib/libssl.so
download-file: /usr/lib/libcrypto.so
download-file: _deps/cpr-build/cpr/libcpr.so.1.9.0
download-file: /usr/local/lib/libcurl.so.4.8.0
download-file: CMakeFiles/download-file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable download-file"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/download-file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/download-file.dir/build: download-file
.PHONY : CMakeFiles/download-file.dir/build

CMakeFiles/download-file.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/download-file.dir/cmake_clean.cmake
.PHONY : CMakeFiles/download-file.dir/clean

CMakeFiles/download-file.dir/depend:
	cd /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build /home/marsel/mephi/programming-2/mmarss/project-part-6/download_file/cmake-build/CMakeFiles/download-file.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/download-file.dir/depend

