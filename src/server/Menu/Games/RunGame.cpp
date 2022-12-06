#include "RunGame.h"

#include <unistd.h>

#include <memory>

RunGame::RunGame(std::size_t cant_players)
    : gameLogic(cant_players), gammingEventQueue(), players(),isClosed(false) {}

void RunGame::addPlayer(std::unique_ptr<GamingClient>&& player) {
  this->players.push_back(std::move(player));
}

RunGame::~RunGame() {
  this->gammingEventQueue.clean();
  while(replayQueue.size()>0)replayQueue.pop();
  std::cerr<<"evetQueue clean";
  players.erase(players.begin(),players.end());
}
void RunGame::close() { 
  this->gammingEventQueue.close(); 
  for (auto&& player : players) player->disconect();
  this->isClosed= true;

}
ProtectedQueue<std::shared_ptr<GameCommand> >& RunGame::getRefGamingQueue() {
  return gammingEventQueue;
}


void RunGame::run() {
  try {
    for (auto&& player : players) player->start();
    while (!this->isClosed) {
      //salgo de bucle si esta cerrada la queue
      if (gammingEventQueue.isClose()) throw QueueEx();

      //popeo y ejecuto eventos de jugadores
      while (!gammingEventQueue.is_empty()) {
         gammingEventQueue.pop()->run(gameLogic);
      }

      //simulo
      this->gameLogic.step();

      std::shared_ptr<SnapShot> snap = this->gameLogic.getSnap();
      //obtengo y envio  snapshot de juego a los jugadores
      for (auto&& player : players) {
        player->addSnap(snap);
      }

      if (snap->isTimeZero()) this->endGame();
      
      //guardo sanp para la replay
      replayQueue.push(snap);
      //si es muy largo lo acorto
      if (replayQueue.size()>LREPLAY) replayQueue.pop();


      //revizo si la jugada termino en goal
      //si lo fue  mando la repe
      if(snap->isGoal()) this->sendReplay();

      usleep(1000000 / 120);
    }
  } catch (const QueueEx &e) {
    std::cerr << "Cerramos La Cola"
              << "\n";
      //creo snap vacio y se lo mando a los player para que lanze exc los hilos de send
      std::shared_ptr<SnapShot> snapEx(new SnapShot);
      for (auto&& player : players) {
        player->addSnap( snapEx );
      }

  } catch (const std::exception& err) {
    std::cerr << "Something went wrong and an exception was caught: "
              << err.what() << "\n";
  }
}
void RunGame::sendReplay(){
    while (this->replayQueue.size()>0)
    { 

      std::shared_ptr<SnapShot> snap=replayQueue.front();
      snap->setGoalTrue();
      for (auto&& player : players) {
        player->addSnap(snap);
      }
      replayQueue.pop();
      usleep(1000000 / 120);
    }
    this->gameLogic.reset();
    while (not this->gammingEventQueue.is_empty()) {
        this->gammingEventQueue.pop();
    }
}
void RunGame::endGame(){

  std::shared_ptr<SnapShot> snapFinish=gameLogic.getFinishSnap() ;
  
  for (auto&& player : players) {
    //std::shared_ptr<SnapShot> snapFinish=gameLogic.getFinishSnap() ;
    player->addSnap(snapFinish);
  }
   std::shared_ptr<SnapShot> snapEx(new SnapShot);
  for (auto&& player : players) {
    player->addSnap( snapEx );
  }

  usleep(1000000 / 120);
  this->isClosed=true;
  this->close();
}

