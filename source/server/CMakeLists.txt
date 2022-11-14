add_subdirectory(Menu)
add_library(Server AcceptThread.cpp Server.cpp)
target_link_libraries(Server PUBLIC Menu Game Socket Thread Queue)
