#ifndef __CLIENTS_HANLER_H__
#define __CLIENTS_HANLER_H__
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>

#include "../../../../common/source/Socket/Socket.h"
#include "GammingClient.h"
#include "../Games/GameHandler.h"


class ClientsHandler {
 private:
  std::vector<GammingClient*> clients;
  GameHandler gameHandler;


 public:
  ClientsHandler();

  GammingClient* conectNewGamingClient(Socket&& soktAccepted, int id);

  void cleanDisconectClients();

  void disconectAll();

  ClientsHandler(ClientsHandler &&other);

  ~ClientsHandler();
};
#endif
