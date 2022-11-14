#include "RightCommand.h"

RightCommand::RightCommand(size_t id):GameCommand(id){}
void RightCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_right(id)
}
