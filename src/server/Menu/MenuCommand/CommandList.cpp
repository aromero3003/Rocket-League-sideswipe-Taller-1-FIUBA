#include "CommandList.h"

CommandList::CommandList():Command(){}
void CommandList::run(GameHandler &games) {
  std::string list;
  games.listAllWithOcupation(list);
    response.append("OK\n");
    response.append(list);
  
}
