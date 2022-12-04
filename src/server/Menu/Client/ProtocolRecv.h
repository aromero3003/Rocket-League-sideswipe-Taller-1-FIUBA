#ifndef __PROTOCOLRECV_H__
#define __PROTOCOLRECV_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>

#include "../GameCommand/GameCommandHandler.h"
#include "BlockingQueue.h"
#include "ProtectedQueue.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"

class ProtocolRecv : public Thread {
 private:
  Socket& skt;
  bool was_closed;
  ProtectedQueue<std::shared_ptr<GameCommand> >& eventQueueRef;
  size_t id;
  int8_t reciveCommand();

 public:
  ProtocolRecv(Socket& skt, size_t id,
               ProtectedQueue<std::shared_ptr<GameCommand> >& eventQueue);
  virtual void run() override;
  virtual ~ProtocolRecv(){};
};
#endif
