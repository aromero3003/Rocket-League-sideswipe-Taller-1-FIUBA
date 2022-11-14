cmake_minimum_required(VERSION 2.8)
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


file(GLOB gameLoop_SRC
     "common/source/Queue/*.cpp"
     "common/source/Socket/*.cpp"
     "server/*.cpp"
     "server/source/*.cpp"
     "server/source/Menu/*.cpp"
     "server/source/Menu/Client/*.cpp"
     "server/source/Menu/Games/*.cpp"
     "server/source/Menu/MenuCommand/*.cpp"
     "server/source/Menu/GameCommand/*.cpp"

)
add_executable(gameLoop ${gameLoop_SRC})


target_link_libraries(gameLoop PRIVATE Threads::Threads)
