#include "RunGame.h"
#include <cstdint>
#include <memory>
#include <unistd.h>

#ifdef ALAN_DEBUG
extern Socket alan;
#endif // ALAN_DEBUG

RunGame::RunGame():gameLogic(2){}
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
            GameCommand *command = gammingEventQueue.pop().getCommand();//->run(gameLogic);
            command->run(gameLogic);
#ifdef ALAN_DEBUG
            uint8_t debug_data = command->num;
            bool was_closed = false;
            alan.sendall(&debug_data, 1, &was_closed);
#endif // ALAN_DEBUG
        }
        this->gameLogic.step();

        std::shared_ptr<SnapShot> snap = this->gameLogic.getSnap();
        for (auto player: players) {
            player->addSnap(snap);
        }
        usleep(1000000/120);


    }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: "
                  << err.what() << "\n";

    } }
