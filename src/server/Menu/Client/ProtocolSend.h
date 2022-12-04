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
#include "QueueEx.h"
class ProtocolSend : public Thread {
 private:
  Socket& skt;
  BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueue;
  bool was_closed;
  void sendResponse(std::vector<uint8_t>& response);
  void sendInfo(std::size_t id);
 public:
  ProtocolSend(Socket& skt,
               BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueue,
               std::size_t cant_players
               ,size_t o_id
              );

  virtual void run() override;
  virtual ~ProtocolSend();
};
#endif
