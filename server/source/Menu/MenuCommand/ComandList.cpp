#include "Comand.h"

void ComandList::run(GameHandler& games) {
  std::string list;
  if (games.listAllWithOcupation(list) == OK) {
    response.append("OK\n");
    response.append(list);
  } else {
    response.append("ERROR\n");
  }
  response.append("\n");
}
