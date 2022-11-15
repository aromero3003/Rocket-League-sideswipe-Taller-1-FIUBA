#ifndef __PROTOCOLSEND_H__
#define __PROTOCOLSEND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include "ProtectedQueue.h"
#include "BlockingQueue.h"
#include "thread.h"
#include "socket.h"
#include "liberror.h"
#include "../GameCommand/GameCommandHandler.h"
#include "Snap.h"
class ProtocolSend: public Thread
{
private:
    Socket& skt;
    BlockingQueue<SnapShot>& snapEventQueue;
    bool was_closed;
    void sendResponse(std::vector<uint8_t>& response);
public:
   ProtocolSend(Socket& skt,BlockingQueue<SnapShot>& snapEventQueue);

  virtual void run() override;
    virtual ~ProtocolSend()= default;
  
};
#endif
