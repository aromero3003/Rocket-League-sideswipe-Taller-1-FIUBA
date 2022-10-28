#ifndef __COMANDHANDLER_H__
#define __COMANDHANDLER_H__

#include <exception>
#include <list>
#include <string>
#include <utility>

#include "Comand.h"
#include "../../Game/GameHandler.h"
// encapsula el manejo de memoria de los comandos par apoder
// aplicar RAII y y polimorfismo sin tener q pensar en la liberacion en caso de
// error
class ComandHandler {
 private:
  Comand* comand;

 public:
  ComandHandler();
  void createComand(std::istream& parameters);
  void run(GameHandler& game);
  std::string& getResponse();
  ~ComandHandler();
};

#endif
