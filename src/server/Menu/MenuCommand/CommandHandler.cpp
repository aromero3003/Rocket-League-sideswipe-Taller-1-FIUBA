#include "CommandHandler.h"

CommandHandler::CommandHandler() {}

CommandHandler::~CommandHandler() {}

std::unique_ptr<Command> CommandHandler::createCommand(std::istream &parameters,size_t id) {
    std::string type;
    parameters >> type >> std::ws;

    if (type == "LISTAR") {
        std::unique_ptr<Command>  command(new CommandList(id));
        return command;
    } else if (type == "CREAR") {
        std::unique_ptr<Command>  command(new CommandCreate(parameters,id));
        return command;
    } else if (type == "UNIR") {
        std::unique_ptr<Command>  command(new CommandAdd(parameters,id));
        return command;
    } else if (type == "TRANSFORM") {
        std::unique_ptr<Command>  command(new CommandTransform(id));
        return command;
    } 
    std::unique_ptr<Command>  command(new BadCommand(id));
    return command; 
}
