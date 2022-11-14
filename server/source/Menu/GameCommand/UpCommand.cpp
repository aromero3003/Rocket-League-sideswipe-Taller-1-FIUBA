#include "UpCommand.h"

UpCommand::UpCommand(size_t id):GameCommand(id){}
void UpCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_up(id)
}
