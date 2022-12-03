#include "CommandHandler.h"

CommandHandler::CommandHandler() {}

CommandHandler::~CommandHandler() {}

std::unique_ptr<Command> CommandHandler::createCommand(
    std::istream&& parameters, Socket& skt) {
  std::string type;
  parameters >> type >> std::ws;

  if (type == "LISTAR") {
    std::unique_ptr<Command> command(new CommandList());
    return command;
  } else if (type == "CREAR") {
    std::unique_ptr<Command> command(new CommandCreate(parameters, skt));
    return command;
  } else if (type == "UNIR") {
    std::unique_ptr<Command> command(new CommandAdd(parameters, skt));
    return command;
  } else {
    std::unique_ptr<Command> command(new BadCommand());
    return command;
  }
}