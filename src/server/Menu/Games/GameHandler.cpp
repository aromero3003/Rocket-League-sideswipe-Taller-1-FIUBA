#include "GameHandler.h"

GameHandler::GameHandler() : mutexgames(), games(){}

void GameHandler::addGame(const std::string& name, const int capacity,Socket& o_skt) {
  std::lock_guard<std::mutex> lock(mutexgames);
  games.addGame(name, capacity,o_skt);

}

void GameHandler::listAllWithOcupation(std::string& list) {
  std::lock_guard<std::mutex> lock(mutexgames);
  games.listAllWithOcupation(list);

}

void GameHandler::addPlayerToGame(const std::string& name,Socket& o_skt) {
  std::lock_guard<std::mutex> lock(mutexgames);
  games.addPlayerToGame(name,o_skt);
}
