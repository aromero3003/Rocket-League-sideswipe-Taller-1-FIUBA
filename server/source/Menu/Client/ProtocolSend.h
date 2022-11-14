#ifndef __PROTOCOLSEND_H__
#define __PROTOCOLSEND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../../../../common/source/Socket/Socket.h"
#include "../../../../common/source/Socket/Liberror.h"

#include "../../../../common/source/Queue/protected_queue.h"
#include "../../../../common/source/Queue/blocking_queue.h"
#include "../GameCommand/GameCommandHandler.h"

#include "../../../../common/source/Thread/Thread.h"

#include "Snap.h"
class ProtocolSend: public Thread
{
private:
    Socket& skt;
    BlockingQueue<SnapShot>& snapEventQueue;
    bool was_closed;
    void sendResponse(std::vector<uint8_t>& response);
public:
  explicit ProtocolSend(Socket& skt,BlockingQueue<SnapShot>& snapEventQueue);

  virtual void run() override;
};
#endif
