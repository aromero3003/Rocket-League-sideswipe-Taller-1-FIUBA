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
  Socket& skt;
  size_t id;
 public:
  CommandWithParameters(  Socket& oskt,  size_t oid) : Command(), gameName(),skt(oskt),id(oid) {}
  virtual void run(GameHandler &games) override{};
  virtual ~CommandWithParameters() {}
};

#endif
