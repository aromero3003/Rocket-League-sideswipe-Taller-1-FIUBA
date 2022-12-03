#ifndef __UPRELEASECOMMAND_H__
#define __UPRELEASECOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "GameCommand.h"
class UpReleaseCommand : public GameCommand {
 private:
 public:
  UpReleaseCommand(size_t id);
  void run(GameLogic& gameLogic) override;
  virtual ~UpReleaseCommand() {}
};
#endif
