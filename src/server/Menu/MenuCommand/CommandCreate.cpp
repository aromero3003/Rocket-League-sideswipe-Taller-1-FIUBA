#include "CommandCreate.h"

CommandCreate::CommandCreate(std::istream& paramenters, size_t id) : CommandWithParameters(id) {
  paramenters >> capacity >> std::ws;
  std::getline(paramenters, gameName);
}

void CommandCreate::run() {
  if (games.addGame(std::move(gameName), std::move(capacity)) == OK) {
    response.append("OK\n");
  } 
}


