#ifndef __PROTOCOLSEND_H__
#define __PROTOCOLSEND_H__

#include <arpa/inet.h>

#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "../GameCommand/GameCommandHandler.h"
#include "BlockingQueue.h"
#include "ProtectedQueue.h"
#include "Snap.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
class ProtocolSend : public Thread {
 private:
  Socket& skt;
  BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueue;
  bool was_closed;
  void sendCantPlayers(std::size_t cant_players);
  void sendResponse(std::vector<uint8_t>& response);

 public:
  ProtocolSend(Socket& skt,
               BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueue,
               std::size_t cant_players);

  virtual void run() override;
  virtual ~ProtocolSend() = default;
};
#endif
