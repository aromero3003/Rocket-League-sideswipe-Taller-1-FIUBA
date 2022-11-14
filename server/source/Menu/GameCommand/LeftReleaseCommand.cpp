#include "LeftReleaseCommand.h"

LeftReleaseCommand::LeftReleaseCommand(size_t id):GameCommand(id){}
void LeftReleaseCommand::run(GameLogic& gameLogic) {
    gameLogic.move_release_player_up(id)
}
