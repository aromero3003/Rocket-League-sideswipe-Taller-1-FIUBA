#include "BadCommand.h"

BadCommand::BadCommand(size_t id):Command(id){}
void BadCommand::run() {
  std::string list;
  if (games.listAllWithOcupation(list) == OK) {
    response.append("OK\n");
    response.append(list);
  } 
}
