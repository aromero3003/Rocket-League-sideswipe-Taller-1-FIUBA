#include "CommandCreate.h"

CommandCreate::CommandCreate(std::istream& paramenters,Socket& o_skt,size_t o_id)  
  : CommandWithParameters( o_skt, o_id) {
  paramenters >> capacity >> std::ws;
  std::getline(paramenters, gameName);
}

void CommandCreate::run(GameHandler &games) {
  games.addGame(std::move(gameName), std::move(capacity),this->skt,this->id) ;
    response.append("Added In Game");
  
}


