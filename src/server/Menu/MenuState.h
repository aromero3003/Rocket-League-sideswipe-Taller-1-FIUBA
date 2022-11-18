#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

#include "socket.h"
#include "Client/ClientsHandler.h"
#include "Games/GameHandler.h"
#include "Menu.h"
#include <memory.h>

class MenuState {
 private:
  ClientsHandler clientsHandler;
  GameHandler gameHandler;
  Menu & menuRef;  //requiero esto para que los hilos que cree puedan añadir eventos al menu

 public:
  MenuState();
  void conectNewClient(Socket&& sktAccepted,size_t id);
  //mandar ref de menu en cada method NO OLVIDAR(almenos en la cracion MenuClient, RunGame)
  void disconectAll();
  /*
  void startGame();
  */
  virtual ~Menu() = default;
};
#endif
