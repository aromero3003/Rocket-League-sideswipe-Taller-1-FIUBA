#include "Command.h"

Command::Command(size_t id) :MenuEvent(), response(),id(id) {}

std::string& Command::getResponse() { return response; }
