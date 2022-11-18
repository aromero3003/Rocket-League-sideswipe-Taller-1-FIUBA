#ifndef __COMMANDWITHPARAMETERS_H__
#define __COMMANDWITHPARAMETERS_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameHandler.h"
#include "Command.h"


class CommandWithParameters : public Command {
 protected:
  std::string gameName;

 public:
  CommandWithParameters(size_t id) : Command(id), gameName() {}
  virtual void run() override{};
  virtual ~CommandWithParameters() {}
};

#endif
