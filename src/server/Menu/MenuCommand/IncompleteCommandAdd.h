#ifndef __INCOMPLETECOMANDADD_H__
#define __INCOMPLETECOMANDADD_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "CommandWithParameters.h"
#include "socket.h"

////ADD
class IncompleteCommandAdd : public CommandWithParameters {
 private:
     std::istream& paramenters;
 public:
  IncompleteCommandAdd(std::istream& paramenters);
  void run(GameHandler &games) override;
  std::istream& getParameters();
  virtual ~IncompleteCommandAdd() {}
};

#endif
