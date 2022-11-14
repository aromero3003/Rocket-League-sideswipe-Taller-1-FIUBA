cmake_minimum_required(VERSION 2.4)
project(Rocket-league)

#standard c++
set(CMAKE_CXX_STANDARD 17)

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")

# threads
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory("server")

include_directories(${PROJECT_SOURCE_DIR}/server/source)

add_executable(hello server/main.cpp)
#add_executable(alan test.cpp)
#target_link_libraries(alan PUBLIC SDL2pp)

