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
  explicit CommandList(size_t id);
  void run() override;
  virtual ~CommandList() {}
};

#endif
