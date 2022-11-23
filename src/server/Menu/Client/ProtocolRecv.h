#ifndef __PROTOCOLRECV_H__
#define __PROTOCOLRECV_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>


#include "ProtectedQueue.h"
#include "BlockingQueue.h"
#include "thread.h"
#include "socket.h"
#include "liberror.h"
#include "../GameCommand/GameCommandHandler.h"



class ProtocolRecv: public Thread 
{
private:
    Socket& skt;
    bool was_closed;
    ProtectedQueue<GameCommandHandler> &eventQueueRef;
    size_t id;
    int8_t reciveCommand();
public:
    ProtocolRecv(Socket& skt ,size_t id,ProtectedQueue<GameCommandHandler>& eventQueue);
    virtual void run() override;
    virtual ~ProtocolRecv()= default;
};
#endif
