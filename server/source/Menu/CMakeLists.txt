add_library(Menu Menu.cpp )
add_subdirectory(Client GameCommand Games MenuCommand)
target_link_libraries(Menu PUBLIC Client GameCommand Games MenuCommand)

