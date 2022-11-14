#include "UpCommand.h"

void UpCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_up(id)
}
