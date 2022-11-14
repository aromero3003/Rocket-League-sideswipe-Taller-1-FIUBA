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

#include_directories(${PROJECT_SOURCE_DIR}/common/source/Socket
#                    ${PROJECT_SOURCE_DIR}/common/source/Thread
#                    ${PROJECT_SOURCE_DIR}/common/source/Queue)

include_directories(${PROJECT_SOURCE_DIR}/common/Socket
                    ${PROJECT_SOURCE_DIR}/common/Thread
                    ${PROJECT_SOURCE_DIR}/common/Queue)

add_subdirectory(source)
add_subdirectory(common/Queue)
add_subdirectory(common/Socket)
add_subdirectory(common/Thread)
########include_subdirectory(../common/source)

add_executable(hello main.cpp)
target_link_libraries(hello PUBLIC Source Socket Thread Queue)
