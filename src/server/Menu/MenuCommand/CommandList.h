#ifndef __COMMANDLIST_H__
#define __COMMANDLIST_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameHandler.h"
#include "Command.h"

class CommandList : public Command {
 public:
  CommandList() : Command() {}
  void run(GameHandler& gameHandler) override;
  virtual ~CommandList() {}
};

#endif
