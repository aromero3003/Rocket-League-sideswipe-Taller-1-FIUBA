#include "Comand.h"
ComandAdd::ComandAdd(std::istream& paramenters) : ComandWithParameters() {
  std::getline(paramenters, gameName);
}
void ComandAdd::run(GameHandler& games) {
  if (games.addPlayerToGame(gameName) == OK) {
    response.append("OK\n");
  } else {
    response.append("ERROR\n");
  }
  response.append("\n");
}
