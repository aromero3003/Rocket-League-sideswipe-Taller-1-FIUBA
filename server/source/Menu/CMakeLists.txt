add_library(Menu Menu.cpp)
add_subdirectory(MenuCommand Client)
add_subdirectory(MenuCommand Game)
target_include_directories(Menu PUBLIC
    $(CMAKE_SOURCE_DIR)/MenuCommand
    $(CMAKE_SOURCE_DIR)/Client
    $(CMAKE_SOURCE_DIR)/Game
    )
target_link_libraries(Menu PUBLIC Command)

