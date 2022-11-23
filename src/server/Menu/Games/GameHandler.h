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

 public:
  GameHandler();
  void addGame(const std::string& name, const int intcapacity);
  void listAllWithOcupation(std::string& list);
  void addPlayerToGame(const std::string& name,Socket&& o_skt,size_t o_id, int cantPlayers);
  ~GameHandler()=default;
};

#endif
