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
#include <memory>
#include <string>
#include <utility>

#include "../Games/GameLogic.h"
#include "BadCommand.h"
#include "LeftCommand.h"
#include "LeftReleaseCommand.h"
#include "NitroCommand.h"
#include "NitroReleaseCommand.h"
#include "RightCommand.h"
#include "RightReleaseCommand.h"
#include "SpaceCommand.h"
#include "SpaceReleaseCommand.h"
#include "UpCommand.h"
#include "UpReleaseCommand.h"
class GameCommandHandler {
 private:
  bool isEndGame;
  size_t id;
  GameCommand* command;

 public:
  GameCommandHandler(size_t id);
  void createCommand(int8_t parameters);
  GameCommand* getCommand();
};

#endif
