#include "CommandAdd.h"
CommandAdd::CommandAdd(std::istream& paramenters,Socket& o_skt,size_t o_id) 
:  CommandWithParameters(o_skt, o_id) {
  std::getline(paramenters, gameName);
}
void CommandAdd::run(GameHandler &games) {
  games.addPlayerToGame(gameName,this->skt,this->id);
  response.append("Added In Game");

}
