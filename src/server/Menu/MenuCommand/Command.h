#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include "../Exceptions/MenuCommandEx.h"
#include "../Games/GameHandler.h"
class Command {
 protected:
  std::string response;

  virtual void run(GameHandler &games) {};
 public:
  Command();
  void execut(GameHandler &games);
  std::string getResponse();
  virtual ~Command() {}
};

#endif
