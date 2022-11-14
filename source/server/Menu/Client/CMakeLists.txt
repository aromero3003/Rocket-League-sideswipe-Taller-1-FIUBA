add_subdirectory($(CMAKE_SOURCE_DIR)/common/source/Socket)
add_library(Client ClientsHandler.cpp GamingClient.cpp ServerMenuProtocol.cpp ClientsHandler.h)
target_include_directories(Client PUBLIC "${CMAKE_SOURCE_DIR}/common/source/Socket")

