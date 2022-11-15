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
    int reciveCommand();
public:
    ProtocolRecv(Socket &skt,ProtectedQueue<GameCommandHandler> &eventQueue,size_t id);
    virtual void run() override;
};
#endif
