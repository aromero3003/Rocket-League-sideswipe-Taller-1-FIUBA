#include "RunGame.h"

#include <unistd.h>

#include <memory>

RunGame::RunGame(std::size_t cant_players)
    : gameLogic(cant_players), gammingEventQueue(), players() {}

void RunGame::addPlayer(std::unique_ptr<GamingClient>&& player) {
  this->players.push_back(std::move(player));
}

RunGame::~RunGame() {
  this->gammingEventQueue.clean();
  std::cerr<<"evetQueue clean";
  players.erase(players.begin(),players.end());
}
void RunGame::close() { 
  this->gammingEventQueue.close(); 
  for (auto&& player : players) player->disconect();
}
ProtectedQueue<std::shared_ptr<GameCommand> >& RunGame::getRefGamingQueue() {
  return gammingEventQueue;
}


void RunGame::run() {
  try {
    for (auto&& player : players) player->start();
    while (1) {
    
      while (!gammingEventQueue.is_empty()) {
         gammingEventQueue.pop()->run(gameLogic);
        /*std::unique_ptr<GameCommand> command = gammingEventQueue.pop().getCommand();
        command->run(gameLogic);*/
#ifdef ALAN_DEBUG
        uint8_t debug_data = command->num;
        bool was_closed = false;
        alan.sendall(&debug_data, 1, &was_closed);
#endif  // ALAN_DEBUG
      }
      this->gameLogic.step();

      std::shared_ptr<SnapShot> snap = this->gameLogic.getSnap();
      for (auto&& player : players) {
        player->addSnap(snap);
      }
      usleep(1000000 / 120);

      if(gammingEventQueue.isClose()) throw QueueEx();
    }
  } catch (const QueueEx) {
    std::cerr << "Cerramos La Cola"
              << "\n";
      //creo snap vacios para que lanze exc los hilos de send
      for (auto&& player : players) {
        player->addSnap( std::shared_ptr<SnapShot> (new SnapShot));
      }

  } catch (const std::exception& err) {
    std::cerr << "Something went wrong and an exception was caught: "
              << err.what() << "\n";
  }
}
