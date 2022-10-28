add_subdirectory(Game)
add_subdirectory(Menu)
add_library(Source AcceptThread.cpp MyClass.cpp Server.cpp)
target_link_libraries(Source PUBLIC Menu Game)
