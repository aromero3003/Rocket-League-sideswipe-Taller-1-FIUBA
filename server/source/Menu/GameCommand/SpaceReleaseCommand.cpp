#include "SpaceReleaseCommand.h"

SpaceReleaseCommand::SpaceReleaseCommand(size_t id):GameCommand(id){}
void SpaceReleaseCommand::run(GameLogic& gameLogic) {
    gameLogic.move_release_player_up(id);
}
