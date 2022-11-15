#ifndef __PROTOCOLRECV_H__
#define __PROTOCOLRECV_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>
#include "../../../../common/source/Socket/Socket.h"
#include "../../../../common/source/Socket/Liberror.h"

#include "../../../../common/source/Queue/protected_queue.h"
#include "../../../../common/source/Queue/blocking_queue.h"
#include "../GameCommand/GameCommandHandler.h"

#include "../../../../common/source/Thread/Thread.h"


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
