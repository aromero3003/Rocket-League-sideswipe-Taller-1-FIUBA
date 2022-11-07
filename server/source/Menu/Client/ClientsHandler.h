#ifndef __CLIENTS_HANLER_H__
#define __CLIENTS_HANLER_H__
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>

#include "../common/source/socket.h"
#include "GammingClient.h"
#include "../Games/GameHandler.h"
class ClientsHandler {
 private:
  std::vector<GammingClient&> clients;

  GammingClient& addGammingClient(Socket&& soktAccepted,ProtectedQueue<CommandGame> &eventQueue);

 public:
  ClientsHandler();

  GammingClient& conectNewGamingClient(Socket&& soktAccepted,ProtectedQueue<CommandGame> &eventQueue);

  void cleanDisconectClients();

  void disconectAll();

  ~ClientsHandler();
};
#endif
