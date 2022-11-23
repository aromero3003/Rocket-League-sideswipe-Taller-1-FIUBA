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
     Socket skt;
     size_t id;
 public:
  CommandAdd(std::istream& paramenters,Socket&& o_skt,size_t o_id);
  void run(GameHandler &games) override;
  void setup(Socket&& o_skt,size_t o_id);
  virtual ~CommandAdd() {}
};

#endif
