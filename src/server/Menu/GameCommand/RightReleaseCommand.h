#ifndef __RIGHTRELEASECOMMAND_H__
#define __RIGHTRELEASECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class RightReleaseCommand : public GameCommand {
 private:
 public:
  RightReleaseCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~RightReleaseCommand() {}
};
#endif
