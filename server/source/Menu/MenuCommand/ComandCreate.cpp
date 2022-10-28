#include "Comand.h"

void ComandCreate::run(GameHandler& games) {
  if (games.addGame(std::move(gameName), std::move(capacity)) == OK) {
    response.append("OK\n");
  } else {
    response.append("ERROR\n");
  }
  response.append("\n");
}

ComandCreate::ComandCreate(std::istream& paramenters) : ComandWithParameters() {
  paramenters >> capacity >> std::ws;
  std::getline(paramenters, gameName);
}
