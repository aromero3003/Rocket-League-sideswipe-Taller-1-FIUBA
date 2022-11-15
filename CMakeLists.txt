cmake_minimum_required(VERSION 2.4)
project(Rocket-league)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
#standard c++
set(CMAKE_CXX_STANDARD 17)

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")

# threads
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/libs/box2d/include)

file(GLOB gameLoop_SRC    
 "common/source/Queue/*.h"
"common/source/Socket/*.h"
"common/source/Thread/*.h"
"server/*.h"
"server/source/*.h"
"server/source/Menu/*.h"
"server/source/Menu/Client/*.h"
"server/source/Menu/Games/*.h"
"server/source/Menu/Games/GameObjects/*.h"
"server/source/Menu/MenuCommand/*.h"
"server/source/Menu/GameCommand/*.h"

     "common/source/Queue/*.cpp"
     "common/source/Socket/*.cpp"
     "common/source/Thread/*.cpp"
     "server/*.cpp"
     "server/source/*.cpp"
     "server/source/Menu/*.cpp"
     "server/source/Menu/Client/*.cpp"
     "server/source/Menu/Games/*.cpp"

     "server/source/Menu/Games/GameObjects/*.cpp"
     "server/source/Menu/MenuCommand/*.cpp"
     "server/source/Menu/GameCommand/*.cpp"

)
add_executable(gameLoop ${gameLoop_SRC})
add_executable(client_debug test_client.cpp
    common/source/Socket/Socket.cpp
    common/source/Socket/Resolver.cpp
    common/source/Socket/Liberror.cpp
    common/source/Socket/ResolverError.cpp)

target_link_libraries(gameLoop PUBLIC box2d)
#target_link_libraries(gameLoop PRIVATE Threads::Threads)
