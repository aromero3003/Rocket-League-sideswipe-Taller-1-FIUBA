#include "CommandHandler.h"

CommandHandler::CommandHandler():isEnd(false) {}

CommandHandler::~CommandHandler() {}

std::unique_ptr<Command> CommandHandler::createCommand(std::istream &&parameters) {
    std::string type;
    parameters >> type >> std::ws;

    if (type == "LISTAR") {
        std::unique_ptr<Command>  command(new CommandList());
        return command;
    } else if (type == "CREAR") {
        std::unique_ptr<Command>  command(new CommandCreate(parameters));
        return command;
    } else if (type == "UNIR") {
        std::unique_ptr<Command>  command(new IncompleteCommandAdd(parameters));
        this->isEnd=true;
        return command;
    }   else {
        std::unique_ptr<Command>  command(new BadCommand());
        return command; 
    }
    
}

bool CommandHandler::isAdd() { return !isEnd;}
