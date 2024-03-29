#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#include <memory.h>

#include <exception>
#include <list>
#include <string>
#include <utility>

#include "BadCommand.h"
#include "Command.h"
#include "CommandAdd.h"
#include "CommandCreate.h"
#include "CommandList.h"
// encapsula el manejo de memoria de los comandos par apoder
// aplicar RAII y y polimorfismo sin tener q pensar en la liberacion en caso de
// error
class CommandHandler {
 private:
 public:
  CommandHandler();
  std::unique_ptr<Command> createCommand(std::istream&& parameters,
                                         Socket& skt);

  ~CommandHandler();
};

#endif
