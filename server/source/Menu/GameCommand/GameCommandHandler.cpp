#include "GameCommandHandler.h"


GameCommandHandler::GameCommandHandler(size_t id):isEndGame(false),id(id) {}

void GameCommandHandler::createCommand(std::istream &parameters) {
    std::string type;
    parameters >> type >> std::ws;

    if (type == "LISTAR") {
        
    } else if (type == "CREAR") {
        
    } else if (type == "UNIR") {
        
    } else {
        throw std::invalid_argument("tipo de comando no encontrado :" + type);
    }
}

bool GameCommandHandler::isEnd() { return isEndGame;}

std::unique_ptr<GameCommand> GameCommandHandler::getCommand() {
    std::unique_ptr<GameCommand>  command(new UpCommand());
    return command;
}

