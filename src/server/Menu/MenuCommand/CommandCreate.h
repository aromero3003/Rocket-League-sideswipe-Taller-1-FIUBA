#ifndef __COMMANDCREATE_H__
#define __COMMANDCREATE_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "CommandWithParameters.h"

// CREATE
class CommandCreate : public CommandWithParameters {
 private:
  int capacity;

 public:
  CommandCreate(std::istream& paramenters, Socket& skt);
  void run(GameHandler& games) override;
  virtual ~CommandCreate() {}
};

#endif
