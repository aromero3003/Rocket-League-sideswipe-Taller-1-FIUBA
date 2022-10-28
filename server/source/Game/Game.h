#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <list>
#include <string>
#include <utility>
class Game {
 private:
  int capacity;
  int occupation;

 public:
  explicit Game(const int capacity);

  void addPlayer();

  bool isComplete();

  std::string getOccupation();
};
#endif
