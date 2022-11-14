#ifndef __MENU_H__
#define __MENU_H__

#include "../../../common/source/socket.h"
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
  void conectNewClient(std::move(sktAccepted));
  void cleanDisconectClients();
  void disconectAll();
  void starGame();
  virtual ~Menu() = default;
};
#endif
