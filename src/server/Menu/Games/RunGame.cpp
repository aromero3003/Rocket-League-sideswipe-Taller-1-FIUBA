#include "RunGame.h"
#include <memory>
#include <unistd.h>

RunGame::RunGame():
gameLogic(2),gammingEventQueue(),players(){}
void RunGame::addPlayer(std::unique_ptr<GamingClient>&& player) {
    this->players.push_back(std::move(player));
}
  ProtectedQueue<GameCommandHandler> & RunGame::getRefGamingQueue(){
    return gammingEventQueue;
  }


void RunGame::run() {
  try {
      for(auto &&player : players)
          player->start();
    while(1){

        while (! gammingEventQueue.is_empty()) {
            gammingEventQueue.pop().getCommand()->run(gameLogic);
        }
        this->gameLogic.step();

        std::shared_ptr<SnapShot> snap = this->gameLogic.getSnap();
        for (auto && player : players) {
            player->addSnap(snap);
        }
        usleep(1000000/120);


    }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: "
                  << err.what() << "\n";

    } }
