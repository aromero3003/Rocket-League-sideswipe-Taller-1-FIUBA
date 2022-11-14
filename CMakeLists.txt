cmake_minimum_required(VERSION 2.8)

project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(APPLE)
  message("Estoy en OSX")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
add_subdirectory(libs/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})


add_executable (gameLoop
    src/client/main.cpp
    src/client/ball.cpp
    src/client/car.cpp
    src/client/client_interface.cpp
    src/client/receiverThread.cpp
    src/client/thread.cpp
    src/client/liberror.cpp
    src/client/resolver.cpp
    src/client/resolvererror.cpp
    src/client/senderThread.cpp
    src/client/socket.cpp
    src/client/world.cpp
)


target_link_libraries(gameLoop PRIVATE Threads::Threads)
target_link_libraries(gameLoop ${SDL2PP_LIBRARIES})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
