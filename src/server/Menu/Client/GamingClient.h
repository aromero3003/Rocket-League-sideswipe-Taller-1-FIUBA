#ifndef __GAMMINGCLIENT_H__
#define __GAMMINGCLIENT_H__

#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "../GameCommand/GameCommandHandler.h"
#include "BlockingQueue.h"
#include "ProtectedQueue.h"
#include "ProtocolRecv.h"
#include "ProtocolSend.h"
#include "Snap.h"
#include "liberror.h"
#include "socket.h"
class GamingClient {
 private:
  size_t id;
  Socket skt;
  BlockingQueue<std::shared_ptr<SnapShot>> snapEventQueue;
  ProtocolSend protocolSend;
  ProtocolRecv protocolRecv;

 public:
  GamingClient(Socket&& skt, size_t id,
               ProtectedQueue<std::shared_ptr<GameCommand> >& eventQueue,
               std::size_t cant_players);
  bool isDisconect();
  void addSnap(std::shared_ptr<SnapShot> snap);
  void start();
  void disconect();
  ~GamingClient();
};
#endif
