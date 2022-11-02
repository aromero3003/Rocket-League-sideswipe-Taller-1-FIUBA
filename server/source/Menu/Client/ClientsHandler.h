#ifndef __CLIENTS_HANLER_H__
#define __CLIENTS_HANLER_H__
#include <algorithm>
#include <utility>
#include <vector>

#include "../common_src/socket.h"
#include "ClientHandler.h"
#include "../Games/GameHandler.h"
class ClientsHandler {
 private:
  std::vector<ClientHandler*> clients;
  GameHandler gameHandler;

  ClientHandler* addClient(Socket&& soktAccepted);
  void startConect(ClientHandler* client);

 public:
  ClientsHandler();

  void conectNewClient(Socket&& soktAccepted);

  void cleanDisconectClients();

  void disconectAll();

  ~ClientsHandler();
};
#endif
