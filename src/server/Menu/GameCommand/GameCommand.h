#ifndef __GAMECOMMAND_H__
#define __GAMECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameLogic.h"
class GameCommand {
 protected:
  size_t id;

 public:
  GameCommand(size_t id);
  virtual void run(GameLogic& gameLogic) = 0;
  virtual ~GameCommand() = default;
  int num;
};
#endif
