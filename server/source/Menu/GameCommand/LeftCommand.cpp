#include "LeftCommand.h"

LeftCommand::LeftCommand(size_t id):GameCommand(id){}
void LeftCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_left(id)
}
