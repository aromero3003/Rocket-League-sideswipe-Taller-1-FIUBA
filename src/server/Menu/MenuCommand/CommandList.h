#ifndef __COMMANDLIST_H__
#define __COMMANDLIST_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "Command.h"
class CommandList : public Command {
 public:
  explicit CommandList();
  void run(GameHandler &games) override;
  virtual ~CommandList() {}
};

#endif
