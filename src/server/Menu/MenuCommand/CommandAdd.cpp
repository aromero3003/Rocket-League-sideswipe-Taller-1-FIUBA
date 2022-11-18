#include "CommandAdd.h"
CommandAdd::CommandAdd(std::istream& paramenters, size_t id) : CommandWithParameters(id) {
  std::getline(paramenters, gameName);
}
void CommandAdd::run() {
  if (games.addPlayerToGame(gameName) == OK) {
    response.append("OK\n");
  }
}
