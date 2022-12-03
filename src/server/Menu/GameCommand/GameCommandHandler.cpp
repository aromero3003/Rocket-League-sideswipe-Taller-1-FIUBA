#include "GameCommandHandler.h"

#include <iostream>
#include <memory>

#include "GameCommand.h"
GameCommandHandler::GameCommandHandler(size_t id) : isEndGame(false), id(id) {}

void GameCommandHandler::createCommand(int8_t parameter) {
  std::cerr << "Commando: " << (int)parameter << std::endl;
  if (parameter == PRESS_LEFT) {
    this->command = new LeftCommand(id);
  } else if (parameter == PRESS_RIGHT) {
    this->command = new RightCommand(id);
  } else if (parameter == PRESS_SPACE) {
    this->command = new SpaceCommand(id);
  } else if (parameter == PRESS_SHIFT) {
    this->command = new NitroCommand(id);
  } else if (parameter == RELEASE_LEFT) {
    this->command = new LeftReleaseCommand(id);
  } else if (parameter == RELEASE_RIGHT) {
    this->command = new RightReleaseCommand(id);
  } else if (parameter == RELEASE_SPACE) {
    this->command = new SpaceReleaseCommand(id);
  } else if (parameter == RELEASE_SHIFT) {
    this->command = new NitroReleaseCommand(id);
  } else {
    this->command = new BadGameCommand(id);
  }
}

GameCommand* GameCommandHandler::getCommand() { return this->command; }
