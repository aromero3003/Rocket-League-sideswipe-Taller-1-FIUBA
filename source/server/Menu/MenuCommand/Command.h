#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include "../Games/GameHandler.h"

class Command {
 protected:
  std::string response;

 public:
  Command() : response() {}
  std::string& getResponse();
  virtual void run(GameHandler& gameHandler) = 0;
  virtual ~Command() {}
};

#endif
