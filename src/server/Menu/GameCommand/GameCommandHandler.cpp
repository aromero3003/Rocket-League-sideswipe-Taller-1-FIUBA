#include "GameCommandHandler.h"
#include "GameCommand.h"

#include <iostream>
#include <memory>
GameCommandHandler::GameCommandHandler(size_t id):isEndGame(false),id(id) {}

void GameCommandHandler::createCommand(int8_t parameter) {

    std::cerr << "Commando: " << parameter << std::endl;
    if (parameter == PRESS_LEFT) {
        this->command = new LeftCommand(id);
    } else     if (parameter == PRESS_RIGHT) {
        this->command = new RightCommand(id);
    } else     if (parameter == PRESS_SPACE) {
        this->command = new SpaceCommand(id);
    } else     if (parameter == PRESS_UP) {
        this->command = new UpCommand(id);
    } else     if (parameter == RELEASE_LEFT) {
        this->command = new LeftReleaseCommand(id);
    } else     if (parameter == RELEASE_RIGHT) {
        this->command = new RightReleaseCommand(id);
    } else     if (parameter == RELEASE_SPACE) {
        this->command = new SpaceReleaseCommand(id);
    } else     if (parameter == RELEASE_UP) {
        this->command = new UpReleaseCommand(id);
    }  
}

bool GameCommandHandler::isEnd() { return isEndGame;}

GameCommand* GameCommandHandler::getCommand() {
        return this->command;
}

