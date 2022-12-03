#ifndef __DOWNCOMMAND_H__
#define __DOWNCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class SpaceCommand : public GameCommand {
 private:
 public:
  SpaceCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~SpaceCommand() {}
};
#endif
