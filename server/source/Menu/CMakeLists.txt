add_library(Menu Menu.cpp Menu.h)
add_subdirectory(MenuCommand)
target_link_libraries(Menu PUBLIC Command)

