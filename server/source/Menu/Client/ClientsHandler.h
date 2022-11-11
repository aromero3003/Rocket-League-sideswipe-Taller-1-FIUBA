#ifndef __CLIENTS_HANLER_H__
#define __CLIENTS_HANLER_H__
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>

#include "../common/source/socket.h"
#include "GammingClient.h"
#include "../GameCommand/GameCommand.h"
class ClientsHandler {
 private:
  std::vector<GammingClient*> clients;


 public:
  ClientsHandler();

  GammingClient* conectNewGamingClient(Socket&& soktAccepted, int id);

  void cleanDisconectClients();

  void disconectAll();

  ~ClientsHandler();
};
#endif
