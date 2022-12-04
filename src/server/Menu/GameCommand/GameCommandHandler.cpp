#include "GameCommandHandler.h"

#include <iostream>
#include <memory>

#include "GameCommand.h"
GameCommandHandler::GameCommandHandler(size_t id) : isEndGame(false), id(id) {}

std::shared_ptr<GameCommand> GameCommandHandler::createCommand(int8_t parameter) {
  //std::cerr << "Commando: " << (int)parameter << std::endl;
  if (parameter == PRESS_LEFT) {
    return std::shared_ptr<GameCommand> (new LeftCommand(id));
  } else if (parameter == PRESS_RIGHT) {
    return std::shared_ptr<GameCommand> (new RightCommand(id));
  } else if (parameter == PRESS_SPACE) {
    return std::shared_ptr<GameCommand> (new SpaceCommand(id));
  } else if (parameter == PRESS_SHIFT) {
    return std::shared_ptr<GameCommand> (new NitroCommand(id));
  } else if (parameter == RELEASE_LEFT) {
    return std::shared_ptr<GameCommand> (new LeftReleaseCommand(id));
  } else if (parameter == RELEASE_RIGHT) {
   return std::shared_ptr<GameCommand> (new RightReleaseCommand(id));
  } else if (parameter == RELEASE_SPACE) {
    return std::shared_ptr<GameCommand> (new SpaceReleaseCommand(id));
  } else if (parameter == RELEASE_SHIFT) {
   return std::shared_ptr<GameCommand> (new NitroReleaseCommand(id));
  } else {
    return std::shared_ptr<GameCommand> (new BadGameCommand(id));
  }
}


