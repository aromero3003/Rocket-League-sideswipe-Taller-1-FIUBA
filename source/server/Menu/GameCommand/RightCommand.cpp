#include "RightCommand.h"

void RightCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_right(id)
}
