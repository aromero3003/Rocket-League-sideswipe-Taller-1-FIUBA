#ifndef __GAMECOMMANDHANDLER_H__
#define __GAMECOMMANDHANDLER_H__

#include <exception>
#include <list>
#include <string>
#include <utility>

#include "GameCommand.h"
#include "../Games/GameLogic.h"
class GameCommandHandler {
 private:
  GameCommand* command;

 public:
  GameCommandHandler();
  void createCommand(std::istream& parameters);
  GameCommand getCommand();
  ~GameCommandHandler();
};

#endif