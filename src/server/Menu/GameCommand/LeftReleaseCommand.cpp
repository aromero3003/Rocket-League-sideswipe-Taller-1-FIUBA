#include "LeftReleaseCommand.h"

LeftReleaseCommand::LeftReleaseCommand(size_t id):GameCommand(id){}
void LeftReleaseCommand::run(GameLogic& gameLogic) {
    gameLogic.brake_player(this->id);
}
