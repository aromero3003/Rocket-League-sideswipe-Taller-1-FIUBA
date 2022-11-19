#include "RightReleaseCommand.h"

RightReleaseCommand::RightReleaseCommand(size_t id):GameCommand(id){}
void RightReleaseCommand::run(GameLogic& gameLogic) {
    gameLogic.brake_player(this->id);
}
