#include "LeftCommand.h"

void LeftCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_left(id)
}
