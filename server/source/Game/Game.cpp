#include "Game.h"

Game::Game(const int capacity) : capacity(capacity), occupation(1) {}

void Game::addPlayer() {
  if (occupation < capacity) occupation++;
}

bool Game::isComplete() { return occupation == capacity; }
std::string Game::getOccupation() {
  return (std::to_string(occupation) + "/" + std::to_string(capacity));
}
