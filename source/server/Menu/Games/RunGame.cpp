#include "RunGame.h"
RunGame::RunGame():{}

RunGame::~ProtocolSend(){}

ProtectedQueue<GameCommandHandler> & RunGame::getRefGammingQueue(){
    return gammingEventQueue;
}
void   RunGame::addPlayer(GammingClient* gamingClient){
    players.emplace_back(gamingClient);
}
void  RunGame::setupStart(){
    for (GammingClient* player : players){
        player.
    }
}

void RunGame::run() {
  try {
    while(!was_closed){


    }

    }
  } catch (const LibError& err) {

  }
  }