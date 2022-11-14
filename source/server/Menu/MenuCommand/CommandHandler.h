#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#include <exception>
#include <list>
#include <string>
#include <utility>

#include "Command.h"
#include "CommandAdd.h"
#include "CommandCreate.h"
#include "CommandList.h"
#include "../Games/GameHandler.h"
// encapsula el manejo de memoria de los comandos par apoder
// aplicar RAII y y polimorfismo sin tener q pensar en la liberacion en caso de
// error
class CommandHandler {
 private:
  Command* command;

 public:
  CommandHandler();
  void createCommand(std::istream& parameters);
  void run(GameHandler& game);
  std::string& getResponse();
  ~CommandHandler();
};

#endif
