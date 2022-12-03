
#ifndef __NITROCOMMAND_H__
#define __NITROCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class NitroCommand : public GameCommand {
 public:
  NitroCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~NitroCommand() {}
};

#endif
