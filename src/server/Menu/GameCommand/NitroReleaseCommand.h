

#ifndef __NITRORELEASECOMMAND_H__
#define __NITRORELEASECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class NitroReleaseCommand : public GameCommand {
 public:
  NitroReleaseCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~NitroReleaseCommand() {}
};

#endif
