#include "CommandCreate.h"

void CommandCreate::run(GameHandler& games) {
  if (games.addGame(std::move(gameName), std::move(capacity)) == OK) {
    response.append("OK\n");
  } else {
    response.append("ERROR\n");
  }
}

CommandCreate::CommandCreate(std::istream& paramenters) : CommandWithParameters() {
  paramenters >> capacity >> std::ws;
  std::getline(paramenters, gameName);
}
