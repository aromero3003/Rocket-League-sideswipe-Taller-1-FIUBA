#include "RightReleaseCommand.h"

RightReleaseCommand::RightReleaseCommand(size_t id) : GameCommand(id) {
  GameCommand::num = id * 4 + 0;
}
void RightReleaseCommand::run(GameLogic& gameLogic) {
  gameLogic.brake_player(id);
}
