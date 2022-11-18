#ifndef __COMMANDCREATE_H__
#define __COMMANDCREATE_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameHandler.h"
#include "CommandWithParameters.h"

// CREATE
class CommandCreate : public CommandWithParameters {
 private:
  int capacity;

 public:
  CommandCreate(std::istream& paramenters,size_t id);
  void run() override;
  virtual ~CommandCreate() {}
};

#endif
