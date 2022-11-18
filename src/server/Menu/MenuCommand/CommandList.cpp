#include "CommandList.h"

CommandList::CommandList(size_t id):Command(id){}
void CommandList::run() {
  std::string list;
  if (games.listAllWithOcupation(list) == OK) {
    response.append("OK\n");
    response.append(list);
  } else {
    response.append("ERROR\n");
  }
}
