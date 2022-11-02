#include "Games.h"

int Games::addGame(const std::string& name, int capacity) {
  std::map<std::string, Game>::iterator i;
  if (!exists(name, i)) {
    allGames.insert({name, Game(capacity)});
    return OK;
  }
  return ERRORINGAMES;
}

bool Games::exists(const std::string& name,
                   std::map<std::string, Game>::iterator& i) {
  i = allGames.find(name);
  if (i == allGames.end()) {
    return false;
  } else {
    return true;
  }
}

int Games::addPlayerToGame(const std::string& name) {
  std::map<std::string, Game>::iterator i;
  if (exists(name, i)) {
    if (!i->second.isComplete()) {
      i->second.addPlayer();
      if (i->second.isComplete())
        std::cout << "Comenzando partida " << name << "...\n";
      return OK;
    }
  }
  return ERRORINGAMES;
}

int Games::listAllWithOcupation(std::string& list) {
  for (auto& game : allGames) {
    list.append(game.first);
    list.append(" ");
    list.append(game.second.getOccupation());
    list.append("\n");
  }
  return OK;
}
