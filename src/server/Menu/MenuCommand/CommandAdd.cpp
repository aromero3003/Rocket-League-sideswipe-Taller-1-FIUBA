#include "CommandAdd.h"
CommandAdd::CommandAdd(std::istream& paramenters) : CommandWithParameters() {
  std::getline(paramenters, gameName);
}
void CommandAdd::run(GameHandler& games) {
  //try
  //games.addPlayerToGame(gameName,coplete)
  //if compte
  // sendOkComplete(gameName)
  //send ok(cliente)
  ///cacth
  ///sendError(client)
  if (games.addPlayerToGame(gameName) == OK) {
    response.append("OK\n");
  } else {
    response.append("ERROR\n");
  }
}
