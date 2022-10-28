add_library(Menu ClientHandler.cpp ClientsHandler.cpp ClientThread.cpp ServerMenuProtocol.cpp)
add_subdirectory(MenuCommand)
target_link_libraries(Menu PUBLIC Command)

