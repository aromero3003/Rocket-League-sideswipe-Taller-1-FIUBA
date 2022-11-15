#include "RunGame.h"
RunGame::RunGame():gameLogic(2),gammingEventQueue(),players(){}
  ProtectedQueue<GameCommandHandler> & RunGame::getRefGamingQueue(){
    return gammingEventQueue;
  }

void  RunGame::addPlayer(GamingClient* gamingClient){
    players.emplace_back(gamingClient);
}


void RunGame::run() {
  try {
    while(1){
      gammingEventQueue.pop();
    }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: "
                  << err.what() << "\n";

    } }