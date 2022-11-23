#include "CommandAdd.h"
CommandAdd::CommandAdd(std::istream& paramenters,Socket&& o_skt,size_t o_id) :
  CommandWithParameters(),skt(std::move(o_skt)),id(o_id) {
  std::getline(paramenters, gameName);
}
void CommandAdd::run(GameHandler &games) {
  int cantidadPlayers=0;
  games.addPlayerToGame(gameName,std::move(this->skt),this->id, cantidadPlayers);
  response.append("OK\n"+cantidadPlayers);

}
