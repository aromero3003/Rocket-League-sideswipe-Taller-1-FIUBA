cmake_minimum_required(VERSION 3.5)
project(Rocket-league)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

#standard c++
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/box2d)
# compilation flags
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")

# threads
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# DEBUG
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DALAN_DEBUG")



include_directories(${PROJECT_SOURCE_DIR}/src/common)

include_directories(${PROJECT_SOURCE_DIR}/libs/box2d/include)

file(GLOB server_SRC    

     "src/server/Menu/Client/*.cpp"
     "src/server/Menu/Excptions/*.h"
     "src/common/*.cpp"
     "src/server/*.cpp"
     "src/server/Menu/*.cpp"
     "src/server/Menu/Games/*.cpp"
     "src/server/Menu/Games/GameObjects/*.cpp"
     "src/server/Menu/MenuCommand/*.cpp"
     "src/server/Menu/GameCommand/*.cpp"
)
add_executable(server ${server_SRC})


target_link_libraries(server box2d)



set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(APPLE)
  message("Estoy en OSX")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

# Agrego la libreria SDL2pp habilitando manejo de imagenes, letras y sonidos
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
set(SDL2PP_WITH_MIXER YES)
add_subdirectory(libs/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${PROJECT_SOURCE_DIR}/src/Menu)
include_directories(${SDL2PP_INCLUDE_DIRS})

qt5_wrap_ui(UIS_HEADERS
  src/client/menu.ui
)

file(GLOB client_SRC
     "src/client/*.cpp"
     "src/common/*.cpp"
     "src/client/menu.ui"
)

add_executable(client ${client_SRC})

add_executable(client_debug test_client.cpp
    src/common/liberror.cpp
    src/common/resolver.cpp
    src/common/resolvererror.cpp
    src/common/socket.cpp
    src/common/thread.cpp
    )



target_link_libraries(client ${Qt5Widgets_LIBRARIES})
target_link_libraries(client ${SDL2PP_LIBRARIES})
