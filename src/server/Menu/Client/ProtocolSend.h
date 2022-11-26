#ifndef __PROTOCOLSEND_H__
#define __PROTOCOLSEND_H__

#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <string>
#include "ProtectedQueue.h"
#include "BlockingQueue.h"
#include "thread.h"
#include "socket.h"
#include "liberror.h"
#include "../GameCommand/GameCommandHandler.h"
#include "Snap.h"
#include <arpa/inet.h>
class ProtocolSend: public Thread
{
private:
    Socket& skt;
    BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueue;
    bool was_closed;
    void sendCantPlayers( std::size_t cant_players);
    void sendResponse(std::vector<uint8_t>& response);
public:
   ProtocolSend(Socket& skt,BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueue, std::size_t cant_players);

  virtual void run() override;
    virtual ~ProtocolSend()= default;
  
};
#endif
