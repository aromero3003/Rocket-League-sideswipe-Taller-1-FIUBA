#ifndef __GAMECOMMANDHANDLER_H__
#define __GAMECOMMANDHANDLER_H__
#define PRESS_RIGHT 65
#define PRESS_LEFT 66
#define PRESS_SPACE 67
#define PRESS_SHIFT 71

#define RELEASE_RIGHT 68
#define RELEASE_LEFT 69
#define RELEASE_SPACE 70
#define RELEASE_SHIFT 72
#include <cstddef>
#include <exception>
#include <list>
#include <string>
#include <utility>
#include <memory>

#include "UpCommand.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "SpaceCommand.h"
#include "NitroCommand.h"
#include "UpReleaseCommand.h"
#include "LeftReleaseCommand.h"
#include "RightReleaseCommand.h"
#include "SpaceReleaseCommand.h"
#include "NitroReleaseCommand.h"
#include "BadCommand.h"
#include "../Games/GameLogic.h"
class GameCommandHandler {

 private:
  bool isEndGame;
  size_t id;
  GameCommand* command;

 public:
  GameCommandHandler(size_t id);
  void createCommand(int8_t parameters);
  GameCommand* getCommand();
  bool isEnd();
};

#endif
