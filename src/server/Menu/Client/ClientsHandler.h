#ifndef __CLIENTSHANLER_H__
#define __CLIENTSHANLER_H__
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>
#include "socket.h"
#include "GamingClient.h"
#include "MenuClient.h"
#include "../Games/GameHandler.h"

class ClientsHandler {

 private:
  std::vector<std::unique_ptr<MenuClient>> menuclients;
  GameHandler& gamesRef;
 public:
  ClientsHandler(GameHandler& games);

  void conectNewClient(Socket &&skt);
  
  void cleanDisconectClients();

  void disconectAll();

  ~ClientsHandler();
};

#endif
