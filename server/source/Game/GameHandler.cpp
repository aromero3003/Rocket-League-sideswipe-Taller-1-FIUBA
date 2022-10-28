#include "GameHandler.h"

GameHandler::GameHandler() : mutexMap(), games() {}

int GameHandler::addGame(const std::string& name, const int capacity) {
  mutexMap.lock();
  int res = games.addGame(name, capacity);
  mutexMap.unlock();
  return res;
}

int GameHandler::listAllWithOcupation(std::string& list) {
  mutexMap.lock();
  int res = games.listAllWithOcupation(list);
  mutexMap.unlock();
  return res;
}

int GameHandler::addPlayerToGame(const std::string& name) {
  mutexMap.lock();
  int res = games.addPlayerToGame(name);
  mutexMap.unlock();
  return res;
}
