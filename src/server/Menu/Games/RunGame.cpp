#include "RunGame.h"
#include <unistd.h>

RunGame::RunGame():gameLogic(2),gammingEventQueue(),players(){}
  ProtectedQueue<GameCommandHandler> & RunGame::getRefGamingQueue(){
    return gammingEventQueue;
  }

void  RunGame::addPlayer(GamingClient* gamingClient){
    players.emplace_back(gamingClient);
}

void RunGame::run() {
  try {
      for(auto player : players)
          player->start();
    while(1){

        while (! gammingEventQueue.is_empty()) {
            gammingEventQueue.pop().getCommand()->run(gameLogic);
        }
        this->gameLogic.step();

        SnapShot *snap = this->gameLogic.getSnap();
        for (auto player: players) {
            player->addSnap(*snap); // usar smart pointers (no hay free)
        }
        usleep(1000000);


        //std::shared_ptr<SnapShot> this->gameLogic.getSnap();
    }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: "
                  << err.what() << "\n";

    } }
