cmake_minimum_required(VERSION 2.8)

project(Rocket-League)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
#standard c++
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/box2d)
add_subdirectory(libs/libSDL2pp)

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(APPLE)
  message("Estoy en OSX")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${SDL2PP_INCLUDE_DIRS})

file(GLOB client_SRC
     "src/client/*.cpp"
     "src/common/*.cpp"
)

add_executable(client ${client_SRC})




target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(client ${SDL2PP_LIBRARIES})


include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/libs/box2d/include)

file(GLOB server_SRC    
     "src/server/main.cpp"
     "src/server/*.cpp"
     "src/server/Menu/*.cpp"
     "src/server/Menu/Client/*.cpp"
     "src/server/Menu/GameCommand/*.cpp"
     "src/server/Menu/Games/*.cpp"
     "src/server/Menu/MenuCommand/*.cpp"
)
add_executable(server ${server_SRC})

target_link_libraries(server box2d)

