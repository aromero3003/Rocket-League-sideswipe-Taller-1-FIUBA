#ifndef __COMANDADD_H__
#define __COMANDADD_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../Games/GameHandler.h"
#include "CommandWithParameters.h"

////ADD
class CommandAdd : public CommandWithParameters {
 public:
  CommandAdd(std::istream& paramenters, size_t id);
  void run() override;
  virtual ~CommandAdd() {}
};

#endif
