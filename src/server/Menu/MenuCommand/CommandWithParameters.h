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
  CommandWithParameters() : Command(), gameName() {}
  virtual void run(GameHandler &games) override{};
  virtual ~CommandWithParameters() {}
};

#endif
