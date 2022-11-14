#ifndef __GAMEHANDLER_H__
#define __GAMEHANDLER_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>

#include "Games.h"
#include "RunGame.h"

class GameHandler {
 private:
  std::mutex mutexgames;
  Games games;
  RunGame runGame;

 public:
  GameHandler();
  RunGame& addRunGame();
  int addGame(const std::string& name, const int intcapacity);
  
  int addGame(const std::string& name, const int intcapacity);
  int listAllWithOcupation(std::string& list);
  int addPlayerToGame(const std::string& name);
  ~GameHandler()=default;
};

#endif
