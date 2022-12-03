#ifndef __LEFTRELEASECOMMAND_H__
#define __LEFTRELEASECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class LeftReleaseCommand : public GameCommand {
 private:
 public:
  LeftReleaseCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~LeftReleaseCommand() {}
};
#endif
