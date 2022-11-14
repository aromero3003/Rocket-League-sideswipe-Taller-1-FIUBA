add_subdirectory(Menu)
add_library(Source AcceptThread.cpp Server.cpp) #MyClass.cpp)
target_link_libraries(Source PUBLIC Menu Game)
