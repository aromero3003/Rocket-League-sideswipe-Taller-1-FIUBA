#include "CommandTransform.h"

CommandTransform::CommandTransform(size_t id):Command(id){}
void CommandTransform::run() {
  std::string list;
  if (games.listAllWithOcupation(list) == OK) {
    response.append("OK\n");
    response.append(list);
  } 
}
