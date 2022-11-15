#include "GameCommandHandler.h"


GameCommandHandler::GameCommandHandler(size_t id):isEndGame(false),id(id) {}

void GameCommandHandler::createCommand(int parameter) {

    if (parameter == PRESS_LEFT) {
        std::shared_ptr<GameCommand>  command(new LeftCommand(id));
    } else     if (parameter == PRESS_RIGHT) {
        std::shared_ptr<GameCommand>  command(new RightCommand(id));
    } else     if (parameter == PRESS_SPACE) {
        std::shared_ptr<GameCommand>  command(new SpaceCommand(id));
    } else     if (parameter == PRESS_UP) {
        std::shared_ptr<GameCommand>  command(new UpCommand(id));
    } else     if (parameter == RELEASE_LEFT) {
        std::shared_ptr<GameCommand>  command(new LeftReleaseCommand(id));
    } else     if (parameter == RELEASE_RIGHT) {
        std::shared_ptr<GameCommand>  command(new RightReleaseCommand(id));
    } else     if (parameter == RELEASE_SPACE) {
        std::shared_ptr<GameCommand>  command(new SpaceReleaseCommand(id));
    } else     if (parameter == RELEASE_UP) {
        std::shared_ptr<GameCommand>  command(new UpReleaseCommand(id));
    }  
}

bool GameCommandHandler::isEnd() { return isEndGame;}

std::shared_ptr<GameCommand> GameCommandHandler::getCommand() {
        return std::move(command);
}

