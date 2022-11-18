#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include "MenuEvent.h"

class Command: public MenuEvent {
 protected:
  std::string response;
  size_t id;

 public:
  Command(size_t id);
  std::string& getResponse();
  virtual void run() = 0;
  virtual ~Command() {}
};

#endif
