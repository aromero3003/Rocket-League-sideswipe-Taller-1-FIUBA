#include "GameHandler.h"

GameHandler::GameHandler() : mutexgames(), games(), runGame() {}

int GameHandler::addGame(const std::string& name, const int capacity) {
  mutexgames.lock();
  int res = games.addGame(name, capacity);
  mutexgames.unlock();
  return res;
}
  RunGame& GameHandler::addRunGame(){
      return runGame;
  }
int GameHandler::listAllWithOcupation(std::string& list) {
  mutexgames.lock();
  int res = games.listAllWithOcupation(list);
  mutexgames.unlock();
  return res;
}

int GameHandler::addPlayerToGame(const std::string& name) {
  mutexgames.lock();
  int res = games.addPlayerToGame(name);
  //addPlayerToGame game devolvera
  //if complete 
  //tranform to thread  game t o rungame
  //borrar game? (notrungames)   game monitor<-es donde estoy
  //rungame . inicar (game)
  //return game
  mutexgames.unlock();
  return res;
}
