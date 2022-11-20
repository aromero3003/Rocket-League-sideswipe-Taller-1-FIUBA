

#include "NitroReleaseCommand.h"

NitroReleaseCommand::NitroReleaseCommand(size_t id):GameCommand(id){}
void NitroReleaseCommand::run(GameLogic& gameLogic) {
    gameLogic.deactivate_nitro_player(id);
}
