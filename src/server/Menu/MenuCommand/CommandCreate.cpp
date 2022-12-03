#include "CommandCreate.h"

CommandCreate::CommandCreate(std::istream& paramenters, Socket& o_skt)
    : CommandWithParameters(o_skt) {
  paramenters >> capacity >> std::ws;
  std::getline(paramenters, gameName);
}

void CommandCreate::run(GameHandler& games) {
  games.addGame(std::move(gameName), std::move(capacity), this->skt);
}
