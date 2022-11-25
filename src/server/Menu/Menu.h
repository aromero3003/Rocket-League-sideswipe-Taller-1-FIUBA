#ifndef __MENU_H__
#define __MENU_H__

#include "socket.h"

#include "Client/ClientsHandler.h"
#include "Games/GameHandler.h"


//la idea de la clase es que funcione como un monitor 
//pero sin serlo utiliza threads para la ejecucion de metodos
// y utiliza BlockingQueue para ser threadsafe (sus eventos no generan nuevos eventos)
class Menu {
 private:
  GameHandler gameHandler;
  ClientsHandler clientsHandler;

 public:
  Menu();
  void conectNewClient(Socket&& sktAccepted,size_t id);
   ~Menu();
};
#endif
