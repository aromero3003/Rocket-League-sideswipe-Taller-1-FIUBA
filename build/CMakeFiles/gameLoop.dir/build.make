# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build

# Include any dependencies generated for this target.
include CMakeFiles/gameLoop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gameLoop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gameLoop.dir/flags.make

CMakeFiles/gameLoop.dir/src/client/ball.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/ball.cpp.o: ../src/client/ball.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gameLoop.dir/src/client/ball.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/ball.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/ball.cpp

CMakeFiles/gameLoop.dir/src/client/ball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/ball.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/ball.cpp > CMakeFiles/gameLoop.dir/src/client/ball.cpp.i

CMakeFiles/gameLoop.dir/src/client/ball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/ball.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/ball.cpp -o CMakeFiles/gameLoop.dir/src/client/ball.cpp.s

CMakeFiles/gameLoop.dir/src/client/car.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/car.cpp.o: ../src/client/car.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gameLoop.dir/src/client/car.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/car.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/car.cpp

CMakeFiles/gameLoop.dir/src/client/car.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/car.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/car.cpp > CMakeFiles/gameLoop.dir/src/client/car.cpp.i

CMakeFiles/gameLoop.dir/src/client/car.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/car.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/car.cpp -o CMakeFiles/gameLoop.dir/src/client/car.cpp.s

CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.o: ../src/client/client_interface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/client_interface.cpp

CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/client_interface.cpp > CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.i

CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/client_interface.cpp -o CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.s

CMakeFiles/gameLoop.dir/src/client/main.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/main.cpp.o: ../src/client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/gameLoop.dir/src/client/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/main.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/main.cpp

CMakeFiles/gameLoop.dir/src/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/main.cpp > CMakeFiles/gameLoop.dir/src/client/main.cpp.i

CMakeFiles/gameLoop.dir/src/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/main.cpp -o CMakeFiles/gameLoop.dir/src/client/main.cpp.s

CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.o: ../src/client/receiverThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/receiverThread.cpp

CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/receiverThread.cpp > CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.i

CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/receiverThread.cpp -o CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.s

CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.o: ../src/client/senderThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/senderThread.cpp

CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/senderThread.cpp > CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.i

CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/senderThread.cpp -o CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.s

CMakeFiles/gameLoop.dir/src/client/world.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/client/world.cpp.o: ../src/client/world.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/gameLoop.dir/src/client/world.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/client/world.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/world.cpp

CMakeFiles/gameLoop.dir/src/client/world.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/client/world.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/world.cpp > CMakeFiles/gameLoop.dir/src/client/world.cpp.i

CMakeFiles/gameLoop.dir/src/client/world.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/client/world.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/client/world.cpp -o CMakeFiles/gameLoop.dir/src/client/world.cpp.s

CMakeFiles/gameLoop.dir/src/common/liberror.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/common/liberror.cpp.o: ../src/common/liberror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/gameLoop.dir/src/common/liberror.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/common/liberror.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/liberror.cpp

CMakeFiles/gameLoop.dir/src/common/liberror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/common/liberror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/liberror.cpp > CMakeFiles/gameLoop.dir/src/common/liberror.cpp.i

CMakeFiles/gameLoop.dir/src/common/liberror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/common/liberror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/liberror.cpp -o CMakeFiles/gameLoop.dir/src/common/liberror.cpp.s

CMakeFiles/gameLoop.dir/src/common/resolver.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/common/resolver.cpp.o: ../src/common/resolver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/gameLoop.dir/src/common/resolver.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/common/resolver.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/resolver.cpp

CMakeFiles/gameLoop.dir/src/common/resolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/common/resolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/resolver.cpp > CMakeFiles/gameLoop.dir/src/common/resolver.cpp.i

CMakeFiles/gameLoop.dir/src/common/resolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/common/resolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/resolver.cpp -o CMakeFiles/gameLoop.dir/src/common/resolver.cpp.s

CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.o: ../src/common/resolvererror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/resolvererror.cpp

CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/resolvererror.cpp > CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.i

CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/resolvererror.cpp -o CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.s

CMakeFiles/gameLoop.dir/src/common/socket.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/common/socket.cpp.o: ../src/common/socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/gameLoop.dir/src/common/socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/common/socket.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/socket.cpp

CMakeFiles/gameLoop.dir/src/common/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/common/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/socket.cpp > CMakeFiles/gameLoop.dir/src/common/socket.cpp.i

CMakeFiles/gameLoop.dir/src/common/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/common/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/socket.cpp -o CMakeFiles/gameLoop.dir/src/common/socket.cpp.s

CMakeFiles/gameLoop.dir/src/common/thread.cpp.o: CMakeFiles/gameLoop.dir/flags.make
CMakeFiles/gameLoop.dir/src/common/thread.cpp.o: ../src/common/thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/gameLoop.dir/src/common/thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameLoop.dir/src/common/thread.cpp.o -c /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/thread.cpp

CMakeFiles/gameLoop.dir/src/common/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameLoop.dir/src/common/thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/thread.cpp > CMakeFiles/gameLoop.dir/src/common/thread.cpp.i

CMakeFiles/gameLoop.dir/src/common/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameLoop.dir/src/common/thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/src/common/thread.cpp -o CMakeFiles/gameLoop.dir/src/common/thread.cpp.s

# Object files for target gameLoop
gameLoop_OBJECTS = \
"CMakeFiles/gameLoop.dir/src/client/ball.cpp.o" \
"CMakeFiles/gameLoop.dir/src/client/car.cpp.o" \
"CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.o" \
"CMakeFiles/gameLoop.dir/src/client/main.cpp.o" \
"CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.o" \
"CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.o" \
"CMakeFiles/gameLoop.dir/src/client/world.cpp.o" \
"CMakeFiles/gameLoop.dir/src/common/liberror.cpp.o" \
"CMakeFiles/gameLoop.dir/src/common/resolver.cpp.o" \
"CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.o" \
"CMakeFiles/gameLoop.dir/src/common/socket.cpp.o" \
"CMakeFiles/gameLoop.dir/src/common/thread.cpp.o"

# External object files for target gameLoop
gameLoop_EXTERNAL_OBJECTS =

gameLoop: CMakeFiles/gameLoop.dir/src/client/ball.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/client/car.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/client/client_interface.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/client/main.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/client/receiverThread.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/client/senderThread.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/client/world.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/common/liberror.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/common/resolver.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/common/resolvererror.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/common/socket.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/src/common/thread.cpp.o
gameLoop: CMakeFiles/gameLoop.dir/build.make
gameLoop: /usr/local/lib/libSDL2main.a
gameLoop: libs/libSDL2pp/libSDL2pp.a
gameLoop: /usr/local/lib/libSDL2.so
gameLoop: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
gameLoop: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
gameLoop: CMakeFiles/gameLoop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable gameLoop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gameLoop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gameLoop.dir/build: gameLoop

.PHONY : CMakeFiles/gameLoop.dir/build

CMakeFiles/gameLoop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gameLoop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gameLoop.dir/clean

CMakeFiles/gameLoop.dir/depend:
	cd /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build /home/franco/Taller/Rocket-League-sideswipe-Taller-1-FIUBA/build/CMakeFiles/gameLoop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gameLoop.dir/depend

