#include "GameCommandHandler.h"

#include <iostream>
#include <memory>

#include "GameCommand.h"
GameCommandHandler::GameCommandHandler(size_t id) : isEndGame(false), id(id) {}

void GameCommandHandler::createCommand(int8_t parameter) {
  std::cerr << "Commando: " << (int)parameter << std::endl;
  if (parameter == PRESS_LEFT) {
    std::shared_ptr<GameCommand> (new LeftCommand(id));
  } else if (parameter == PRESS_RIGHT) {
    std::shared_ptr<GameCommand> (new RightCommand(id));
  } else if (parameter == PRESS_SPACE) {
    std::shared_ptr<GameCommand> (new SpaceCommand(id));
  } else if (parameter == PRESS_SHIFT) {
    std::shared_ptr<GameCommand> (new NitroCommand(id));
  } else if (parameter == RELEASE_LEFT) {
    std::shared_ptr<GameCommand> (new LeftReleaseCommand(id));
  } else if (parameter == RELEASE_RIGHT) {
   std::shared_ptr<GameCommand> (new RightReleaseCommand(id));
  } else if (parameter == RELEASE_SPACE) {
    std::shared_ptr<GameCommand> (new SpaceReleaseCommand(id));
  } else if (parameter == RELEASE_SHIFT) {
   std::shared_ptr<GameCommand> (new NitroReleaseCommand(id));
  } else {
    std::shared_ptr<GameCommand> (new BadGameCommand(id));
  }
}

std::shared_ptr<GameCommand>  GameCommandHandler::getCommand() { return this->command; }

