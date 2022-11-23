#include "LeftReleaseCommand.h"

LeftReleaseCommand::LeftReleaseCommand(size_t id):GameCommand(id){GameCommand::num = id*4;}
void LeftReleaseCommand::run(GameLogic& gameLogic) {
    gameLogic.brake_player(id);
}
