#include "LeftCommand.h"
#include "GameCommand.h"

LeftCommand::LeftCommand(size_t id):GameCommand(id){GameCommand::num = 1+id*4;}
void LeftCommand::run(GameLogic& gameLogic) {
    gameLogic.move_player_left(id);
}
