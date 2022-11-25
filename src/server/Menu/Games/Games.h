#ifndef __GAMES_H__
#define __GAMES_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>

#include "../Exceptions/MenuCommandEx.h"
#include "Game.h"
#include "RunGame.h"

class Games {
 private:
  std::map<std::string, Game> allGames;

  std::vector<std::unique_ptr<RunGame>> allRunGames;
  bool exists(const std::string& name,
              std::map<std::string, Game>::iterator& i);
 void startRungame(std::map<std::string, Game>::iterator i);
 
 public:
  Games() : allGames() {}
  void addGame(const std::string& name, const int capacity,Socket& o_skt,size_t o_id);
  void addPlayerToGame(const std::string& name,Socket& o_skt,size_t o_id);
  void listAllWithOcupation(std::string& list);
  ~Games() = default;
};
#endif
