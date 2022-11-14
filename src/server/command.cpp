#include "command.h"

Command::Command(int i, int command_num){
    this->id = i;
    this->command_num = command_num;
}

int Command::get_command(){
    return this->command_num;
}

Command::~Command(){}