#include "SpaceCommand.h"

SpaceCommand::SpaceCommand(size_t id):GameCommand(id){}
void SpaceCommand::run(GameLogic& gameLogic) {
    gameLogic.jump_player(id);
}
