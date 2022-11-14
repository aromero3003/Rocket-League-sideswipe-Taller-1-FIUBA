#ifndef __GAMECOMMANDHANDLER_H__
#define __GAMECOMMANDHANDLER_H__

#include <exception>
#include <list>
#include <string>
#include <utility>
#include <memory>

#include "UpCommand.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "DownCommand.h"
#include "../Games/GameLogic.h"
class GameCommandHandler {
 private:
  bool isEndGame;
  size_t id;
  std::unique_ptr<GameCommand> command;

 public:

  GameCommandHandler():isEndGame(false),id(id){}
  void createCommand(std::istream& parameters);
  std::unique_ptr<GameCommand> getCommand();
  bool isEnd();
  ~GameCommandHandler();
};

#endif
