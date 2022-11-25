#include "CommandCreate.h"

CommandCreate::CommandCreate(std::istream& paramenters) : CommandWithParameters() {
  paramenters >> capacity >> std::ws;
  std::getline(paramenters, gameName);
}

void CommandCreate::run(GameHandler &games) {
  games.addGame(std::move(gameName), std::move(capacity)) ;
    response.append("OK\n");
  
}


