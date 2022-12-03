#ifndef __BADCOMAND_H__
#define __BADCOMAND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "Command.h"

////Bad
class BadCommand : public Command {
 public:
  BadCommand();
  void run(GameHandler &games){};
  virtual ~BadCommand() {}
};

#endif
