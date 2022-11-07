#ifndef __PROTOCOLRECV_H__
#define __PROTOCOLRECV_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../GameCommand/GameCommand.h"
#include "../../common/source/liberror.h"
#include "../../common/source/socket.h"
#include "../Games/GameHandler.h"
#include "../common/source/Thread.h"
#include "../../common/source/protected_queue.h"

class ProtocolRecv: public Thread 
{
private:
    Socket& skt;
    ProtectedQueue<GameCommand> &eventQueue;

public:
    explicit ProtocolRecv(Socket &skt,ProtectedQueue<GameCommand> &eventQueue);
  virtual void run() override;
    void disconcet();
};
#endif