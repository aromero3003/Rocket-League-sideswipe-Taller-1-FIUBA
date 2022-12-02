#ifndef __COMANDADD_H__
#define __COMANDADD_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "CommandWithParameters.h"
#include "socket.h"

////ADD
class CommandAdd : public CommandWithParameters {
 private:

 public:
  CommandAdd(std::istream& paramenters,Socket& o_skt);
  void run(GameHandler &games) override;
  virtual ~CommandAdd() {}
};

#endif
