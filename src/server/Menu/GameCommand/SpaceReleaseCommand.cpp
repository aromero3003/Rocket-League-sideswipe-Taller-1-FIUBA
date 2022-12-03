#include "SpaceReleaseCommand.h"

#include "GameCommand.h"

SpaceReleaseCommand::SpaceReleaseCommand(size_t id) : GameCommand(id) {
  GameCommand::num = id * 4;
}
void SpaceReleaseCommand::run(GameLogic& gameLogic) {
  //    gameLogic.move_release_player_up(id);
}
