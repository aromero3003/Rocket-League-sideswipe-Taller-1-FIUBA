#ifndef __PROTOCOLSEND_H__
#define __PROTOCOLSEND_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../../common/source/liberror.h"
#include "../../common/source/socket.h"
#include "../MenuCommand/CommandHandler.h"
#include "../Games/GameHandler.h"
#include "Snap.h"
#include "../common/source/Thread.h"
class ProtocolSend: public Thread
{
private:
    Socket& skt;
    BlockingQueue<Snap>& snapEventQueue;
public:

    explicit ProtocolSend(Socket&skt, BlockingQueue<Snap>& snapEventQueue);
  virtual void run() override;
    void disconcet();
};
#endif