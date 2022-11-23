#include "GameHandler.h"

GameHandler::GameHandler() : mutexgames(), games(){}

void GameHandler::addGame(const std::string& name, const int capacity) {
  std::lock_guard<std::mutex> lock(mutexgames);
  games.addGame(name, capacity);

}

void GameHandler::listAllWithOcupation(std::string& list) {
  std::lock_guard<std::mutex> lock(mutexgames);
  games.listAllWithOcupation(list);

}

void GameHandler::addPlayerToGame(const std::string& name,Socket&& o_skt,size_t o_id) {
  std::lock_guard<std::mutex> lock(mutexgames);
  games.addPlayerToGame(name,std::move(o_skt),o_id);
}
