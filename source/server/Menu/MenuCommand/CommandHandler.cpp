#include "CommandHandler.h"

CommandHandler::CommandHandler() { command = nullptr; }

CommandHandler::~CommandHandler() {
    if (command) delete command;
}

void CommandHandler::createCommand(std::istream &parameters) {
    std::string type;
    parameters >> type >> std::ws;

    if (type == "LISTAR") {
        command = new CommandList();
    } else if (type == "CREAR") {
        command = new CommandCreate(parameters);
    } else if (type == "UNIR") {
        command = new CommandAdd(parameters);
    } else {
        throw std::invalid_argument("tipo de comando no encontrado :" + type);
    }
}

void CommandHandler::run(GameHandler &games) {
    if (command != nullptr) command->run(games);
}

std::string &CommandHandler::getResponse() { return command->getResponse(); }
