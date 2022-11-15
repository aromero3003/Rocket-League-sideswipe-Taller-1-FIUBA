#ifndef __CLIENTS_HANLER_H__
#define __CLIENTS_HANLER_H__
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>

#include "../../../../common/source/Socket/Socket.h"
#include "GamingClient.h"
#include "../Games/GameHandler.h"


class ClientsHandler {
 private:
  std::vector<GamingClient*> clients;
  GameHandler gameHandler;


 public:
  ClientsHandler();

  GamingClient* conectNewGamingClient(Socket&& soktAccepted, size_t id,ProtectedQueue<GameCommandHandler> &eventQueue);

  void cleanDisconectClients();

  void disconectAll();

  ClientsHandler(ClientsHandler &&other);

  ~ClientsHandler();
};
#endif
