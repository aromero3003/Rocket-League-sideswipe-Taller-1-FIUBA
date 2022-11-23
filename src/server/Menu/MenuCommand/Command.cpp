#include "Command.h"

Command::Command() :response() {}

std::string Command::getResponse() { return this->response; }

void Command::execut(GameHandler &games) {
    try {
        this->run(games);
    } catch(const MenuCommandEx &e) {
        this->response.clear();
        this->response.append("FailRquest");
    }
}