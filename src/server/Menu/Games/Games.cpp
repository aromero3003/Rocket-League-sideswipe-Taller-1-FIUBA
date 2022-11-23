#include "Games.h"

void Games::addGame(const std::string& name, int capacity) {
  std::map<std::string, Game>::iterator i;
  if (!exists(name, i)) {
    allGames.insert({name, Game(capacity)});
  } else {
    throw MenuCommandEx();
  }
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
void Games::startRungame(std::map<std::string, Game>::iterator i){
    allRunGames.push_back(i->second.getRunGame());
    allGames.extract(i);
    allRunGames.back()->start();
} 

void Games::addPlayerToGame(const std::string& name,Socket&& o_skt,size_t o_id,int cantPlayers) {
  std::map<std::string, Game>::iterator i;
  if (exists(name, i)) {
    if (!i->second.isComplete()) {
      i->second.addPlayer(std::move(o_skt),o_id,cantPlayers);
      if (i->second.isComplete())
        startRungame(i);
    }
  } else {
    throw  MenuCommandEx();
  }
}

void Games::listAllWithOcupation(std::string& list) {
  for (auto& game : allGames) {
    list.append(game.first);
    list.append(" ");
    list.append(game.second.getOccupation());
    list.append("\n");
  }
}
