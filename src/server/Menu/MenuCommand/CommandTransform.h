#ifndef __COMMANDTRANSFORM_H__
#define __COMMANDTRANSFORM_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameHandler.h"
#include "Command.h"

class CommandTransform : public Command {
 public:
  explicit CommandTransform(size_t id);
  void run() override;
  virtual ~CommandTransform() {}
};

#endif
