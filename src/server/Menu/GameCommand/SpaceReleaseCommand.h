#ifndef __SAPACERELEASECOMMAND_H__
#define __SAPACERELEASECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class SpaceReleaseCommand : public GameCommand {
 private:
 public:
  SpaceReleaseCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~SpaceReleaseCommand() {}
};
#endif
