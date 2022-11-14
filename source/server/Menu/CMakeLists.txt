add_library(Menu Menu.cpp)
add_subdirectory(MenuCommand)
add_subdirectory(Client)
add_subdirectory(Games)
add_subdirectory(GameCommand)
target_include_directories(Menu PUBLIC
    $(CMAKE_SOURCE_DIR)/MenuCommand
    $(CMAKE_SOURCE_DIR)/GameCommand
    $(CMAKE_SOURCE_DIR)/Client
    $(CMAKE_SOURCE_DIR)/Game
    )
target_link_libraries(Menu PUBLIC Command Games Client)

