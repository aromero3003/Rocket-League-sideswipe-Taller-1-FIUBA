#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>

#include "../Client/GamingClient.h"
#include "../Client/StandbyClient.h"
#include "RunGame.h"
class Game {
 private:
  int capacity;
  int occupation;
  std::vector<std::unique_ptr<StandbyClient>> clients;

 public:
  explicit Game(const int capacity);

  void addPlayer(Socket&& skt);

  std::unique_ptr<RunGame> getRunGame();

  bool isComplete();

  std::string getOccupation();
};
#endif
