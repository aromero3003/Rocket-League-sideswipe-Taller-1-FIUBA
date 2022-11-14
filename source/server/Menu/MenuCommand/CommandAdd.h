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
  explicit CommandAdd(std::istream& paramenters);
  void run(GameHandler& gameHandler) override;
  virtual ~CommandAdd() {}
};

#endif
