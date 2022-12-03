
#include "NitroCommand.h"

NitroCommand::NitroCommand(size_t id) : GameCommand(id) {}
void NitroCommand::run(GameLogic& gameLogic) {
  gameLogic.activate_nitro_player(id);
}
