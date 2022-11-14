#include "DownCommand.h"

void DownCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_down(id)
}
