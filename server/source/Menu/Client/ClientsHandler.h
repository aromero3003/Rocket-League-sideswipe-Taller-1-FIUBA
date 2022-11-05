#ifndef __CLIENTS_HANLER_H__
#define __CLIENTS_HANLER_H__
#include <algorithm>
#include <utility>
#include <vector>

#include "../common_src/socket.h"
#include "GammingClient.h"
#include "../Games/GameHandler.h"
class ClientsHandler {
 private:
  std::vector<GammingClient*> clients;

  GammingClient* addClient(Socket&& soktAccepted);
  void startConect(GammingClient* client);

 public:
  ClientsHandler();

  void conectNewClient(Socket&& soktAccepted);

  void cleanDisconectClients();

  void disconectAll();

  ~ClientsHandler();
};
#endif
