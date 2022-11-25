#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <memory>
#include "RunGame.h"
#include "../Client/StandbyClient.h"
#include "../Client/GamingClient.h"
class Game {
 private:
  int capacity;
  int occupation;
  std::vector<std::unique_ptr<StandbyClient>> clients;
 public:
  explicit Game(const int capacity);

  void addPlayer(Socket&& skt,size_t id, int cantPlayers);

  std::unique_ptr<RunGame> getRunGame();

  bool isComplete();

  std::string getOccupation();
};
#endif
