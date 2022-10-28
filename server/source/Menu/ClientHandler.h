#ifndef __CLIENT_HANLER_H__
#define __CLIENT_HANLER_H__
#include <utility>
#include <vector>

#include "Socket.h"
#include "ClientThread.h"
#include "../Game/GameHandler.h"
class ClientHandler {
 private:
  Socket sktRefOfClient;
  ClientThread clientThread;

 public:
  ClientHandler(Socket&& skt, GameHandler& gameHandler);
  void run();
  bool isDisconect();
  void disconect();

  ~ClientHandler()=default;
};
#endif
