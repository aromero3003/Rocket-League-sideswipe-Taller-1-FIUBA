#ifndef __GAMES_H__
#define __GAMES_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>

#include "Game.h"
#define OK 0
#define ERRORINGAMES -1

class Games {
 private:
  std::map<std::string, Game> allGames;
  bool exists(const std::string& name,
              std::map<std::string, Game>::iterator& i);

 public:
  Games() : allGames() {}
  int addGame(const std::string& name, const int capacity);
  int addPlayerToGame(const std::string& name);
  int listAllWithOcupation(std::string& list);
  ~Games() = default;
};
#endif
