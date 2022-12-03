#include "RightCommand.h"

RightCommand::RightCommand(size_t id) : GameCommand(id) {
  GameCommand::num = 2 + id * 4;
}
void RightCommand::run(GameLogic& gameLogic) {
  gameLogic.move_player_right(id);
}
