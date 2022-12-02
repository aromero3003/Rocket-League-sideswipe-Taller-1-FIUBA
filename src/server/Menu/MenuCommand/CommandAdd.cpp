#include "CommandAdd.h"
CommandAdd::CommandAdd(std::istream& paramenters,Socket& o_skt) 
:  CommandWithParameters(o_skt) {
  std::getline(paramenters, gameName);
}
void CommandAdd::run(GameHandler &games) {
  games.addPlayerToGame(gameName,this->skt);
}
