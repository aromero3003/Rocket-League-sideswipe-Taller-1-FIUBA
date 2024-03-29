#include "Game.h"

Game::Game(const int capacity) : capacity(capacity), occupation(0), clients() {}

void Game::addPlayer(Socket&& skt) {
  if (occupation < capacity) {
    occupation++;
    std::unique_ptr<StandbyClient> client(new StandbyClient(std::move(skt)));
    clients.push_back(std::move(client));
  }
  /// trhow ex
}

std::unique_ptr<RunGame> Game::getRunGame() {
  std::unique_ptr<RunGame> runGame(new RunGame(clients.size()));

  size_t a = 0;
  for (auto&& client : clients) {
    // getGamingClient(runGame->getRefGamingQueue(),clients.size()) <-- crea
    // gaming client (mandas queue y cant playrs)
    runGame->addPlayer(std::move(client->getGamingClient(
        runGame->getRefGamingQueue(), a, clients.size())));
    a++;
  }
  return runGame;
}
bool Game::isComplete() { return occupation == capacity; }
std::string Game::getOccupation() {
  return (std::to_string(occupation) + "/" + std::to_string(capacity));
}
