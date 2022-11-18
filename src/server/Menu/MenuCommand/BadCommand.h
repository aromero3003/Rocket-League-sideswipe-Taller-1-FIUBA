#ifndef __BADCOMMAND_H__
#define __BADCOMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameHandler.h"
#include "Command.h"

class BadCommand : public Command {
 public:
  explicit BadCommand(size_t id);
  void run() override;
  virtual ~BadCommand() {}
};

#endif
