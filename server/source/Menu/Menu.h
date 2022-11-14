#ifndef __MENU_H__
#define __MENU_H__

#include "../../../common/source/Socket/Socket.h"
#include "Client/ClientsHandler.h"
#include "Games/GameHandler.h"
#include "Games/RunGame.h"/// reafactorizar !!!!!!!
class Menu  {
 private:
  ClientsHandler clientsHandler;
  GameHandler gameHandler;
  RunGame& runGame; /// reafactorizar !!!!!!!

 public:
  Menu();
  void conectNewClient(Socket&& sktAccepted,int id);
  void cleanDisconectClients();
  void disconectAll();
  void startGame();
  virtual ~Menu() = default;
};
#endif
