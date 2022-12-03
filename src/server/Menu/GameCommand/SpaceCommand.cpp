#include "SpaceCommand.h"

#include "GameCommand.h"

SpaceCommand::SpaceCommand(size_t id) : GameCommand(id) {
  GameCommand::num = 3 + 4 * id;
}
void SpaceCommand::run(GameLogic& gameLogic) { gameLogic.jump_player(id); }
